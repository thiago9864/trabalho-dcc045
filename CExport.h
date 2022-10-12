#ifndef C_EXPORT_CPP
#define C_EXPORT_CPP

#ifdef __cplusplus
extern "C"
{
#endif // C++ guard

void setObjValue(int v);
void printObjValue();

#ifdef __cplusplus
}
#endif // end C++ guard

#endif // C_EXPORT_CPP