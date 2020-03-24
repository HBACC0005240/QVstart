#pragma once
enum ITDataDefType
{
	DT_None=0x0,		//©у
	DT_FileGroup=0x100,		//д©б╪
	DT_File=0x200,		//нд╪Ч
};

#define freePtr(p) {if (p) {delete p;}}
#define freeAndNil(p) {if (p) {delete p; p = NULL;}}
#define freeAndNilIntf(p) {if (p) {p->Release(); p = NULL;}}
#define freeAndNilArray(p) {if (p) {delete[] p; p = NULL;}}
#define freeAndNilByGFree(p) {if (p) {gFree(p); p = NULL;}}
#define doNothingMacro()

#define MaxInt      0x7FFFFFFF
#define MinInt      0x80000000
#define MaxListSize 0x07FFFFFF
#define MINCHAR     0x80
#define MAXCHAR     0x7f
#define MINSHORT    0x8000
#define MAXSHORT    0x7fff
#define MINLONG     0x80000000
#define MAXLONG     0x7fffffff
#define MINDOUBLE   2.2250738585072014e-308
#define MAXDOUBLE   1.7976931348623158e+308
#define MAXBYTE     0xff
#define MAXWORD     0xffff
#define MAXDWORD    0xffffffff

const long long c_MaxInt64 = 0x7FFFFFFFFFFFFFFF;
const long long c_MinInt64 = 0x8000000000000000;
#   define DEFINE_RESOURCESTRING(name, value) const QString name = QStringLiteral(value)
