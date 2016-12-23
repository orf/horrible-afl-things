#include <Python.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  char *string = malloc(10000000);
  Py_SetProgramName(argv[0]);  /* optional but recommended */
  Py_Initialize();
  PyObject *pModule;
//  PySys_SetPath("/home/tomforbes/p/");
  PyObject *sys_path = PySys_GetObject("path");
  PyList_Append(sys_path, PyUnicode_FromString("."));
  pModule = PyImport_Import(PyUnicode_FromString("PIL._imaging"));
  PyErr_Print();
  //printf("%p", pModule);
  
  PyObject *pFunc = PyObject_GetAttrString(pModule, "pcd_decoder");
 PyErr_Print();
  //printf("%p", pFunc);

  PyObject *pArgs = PyTuple_New(2);
  PyTuple_SetItem(pArgs, 0, PyUnicode_FromString("RGB"));
  PyTuple_SetItem(pArgs, 1, PyUnicode_FromString("pcd"));
  PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
  //printf("%p", pValue);
  PyErr_Print();
  //PyObject_Print(pValue, stdout,Py_PRINT_RAW);


  //Image.core.new(self.mode, self.size)
  PyObject *newImgArgs = PyTuple_New(2);
  PyTuple_SetItem(newImgArgs, 0, PyUnicode_FromString("RGB"));
  
  PyObject *sizeTuple = PyTuple_New(2);
  PyTuple_SetItem(sizeTuple, 0, PyLong_FromLong(768));
  PyTuple_SetItem(sizeTuple, 1, PyLong_FromLong(512));

  PyTuple_SetItem(newImgArgs, 1, sizeTuple);

  PyObject *newImg = PyObject_CallObject(PyObject_GetAttrString(pModule, "new"), newImgArgs);
  //PyObject_Print(newImg, stdout, Py_PRINT_RAW);

  PyObject *setImgArgs = PyTuple_New(1);
  PyTuple_SetItem(setImgArgs, 0, newImg);

  PyObject *setImg = PyObject_GetAttrString(pValue, "setimage");
  PyObject *result = PyObject_CallObject(setImg, setImgArgs);
  //PyObject_Print(result, stdout, Py_PRINT_RAW);

  PyObject *pDecode = PyObject_GetAttrString(pValue, "decode");
  
  //PyObject_Print(pDecode, stdout,Py_PRINT_RAW);


  PyObject *pArgs2 = PyTuple_New(1);

//#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
//#endif
       	int total = read(0, string, 10000);
	string[total] = 0;

/*        FILE *f = fopen(argv[1], "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *string = malloc(fsize + 1);
        fread(string, fsize, 1, f);
        fclose(f);
*/
//        string[fsize] = 0;
//  printf("%i", fsize);
  //return 0;
  PyTuple_SetItem(pArgs2, 0, PyBytes_FromStringAndSize(string, total));
//  PyObject_Print(pArgs2, stdout, Py_PRINT_RAW);
  PyObject *callValue = PyObject_CallObject(pDecode, pArgs2); //Py_BuildValue("y#", "test"));
 // PyObject_Print(callValue, stdout,Py_PRINT_RAW);

//  PyRun_SimpleString("from time import time,ctime\n"
//                     "print('Today is', ctime(time()))\n");

  printf("%p", callValue);
//  Py_Finalize();
  return 0;
}
