#include <stddef.h>
#include <limits.h>

#if defined(ULLONG_MAX) && !defined(TEST_NO_LLONG)
typedef unsigned long long UMAX;
#define UMAX_MAX  ULLONG_MAX
#define UMAX_PRI  "%llu"
#define UMAX_PRIo "%llo"
#define UMAX_PRIx "%llx"
typedef long long SMAX;
#define SMAX_MAX  LLONG_MAX
#define SMAX_MIN  LLONG_MIN
#define SMAX_PRI  "%lld"

#elif defined(_WIN32) && !defined(TEST_NO_I64)
typedef unsigned __int64 UMAX;
#define UMAX_MAX  _UI64_MAX
#define UMAX_PRI  "%I64u"
#define UMAX_PRIo "%I64o"
#define UMAX_PRIx "%I64x"
typedef __int64 SMAX;
#define SMAX_MAX  _I64_MAX
#define SMAX_MIN  _I64_MIN
#define SMAX_PRI  "%I64d"

#else
typedef unsigned long UMAX;
#define UMAX_MAX  ULONG_MAX
#define UMAX_PRI  "%lu"
#define UMAX_PRIo "%lo"
#define UMAX_PRIx "%lx"
typedef long SMAX;
#define SMAX_MAX  LONG_MAX
#define SMAX_MIN  LONG_MIN
#define SMAX_PRI  "%ld"

#endif

#undef STROFINT_UPPERHEX
#define STROFINT_UPPERHEX  (0)

/********** Include StrOfInt for unsigned integer **********/

#undef STROFINT_SIGNED
#define STROFINT_SIGNED  (0)

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfUChar
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  unsigned char
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfUShort
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  unsigned short
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfUInt
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  unsigned int
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfULong
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  unsigned long
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfUMax
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  UMAX
#include <raymai/StrOfInt.h>

/********** Include StrOfInt for signed integer **********/

#undef STROFINT_SIGNED
#define STROFINT_SIGNED  (1)

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfSChar
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  signed char
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfShort
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  short
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfInt
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  int
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfLong
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  long
#include <raymai/StrOfInt.h>

#undef STROFINT_FUNCNAME
#define STROFINT_FUNCNAME  StrOfSMax
#undef STROFINT_INTTYPE
#define STROFINT_INTTYPE  SMAX
#include <raymai/StrOfInt.h>

/*********************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(Func, Int, Fmt, Radix) { \
	enum { nBuf = 99 }; char szPri[nBuf + 1], szBuf[nBuf + 1]; \
	int ret, nPri = sprintf(szPri, Fmt, (Int)); \
	ret = Func(szBuf, nBuf, (Int), (Radix)); \
	assert(ret >= 0); szBuf[ret] = 0; \
	assert(strcmp(szBuf, szPri) == 0); \
	ret = Func(szBuf, nPri, (Int), (Radix)); \
	assert(ret >= 0); szBuf[ret] = 0; \
	assert(strcmp(szBuf, szPri) == 0); \
}

static void TestEdgeCases(void)
{
	TEST(StrOfSChar, SCHAR_MAX, "%d", 10);
	TEST(StrOfSChar, SCHAR_MIN, "%d", 10);
	TEST(StrOfUChar, UCHAR_MAX, "%u", 10);
	TEST(StrOfUChar, UCHAR_MAX, "%o", 8);
	TEST(StrOfUChar, UCHAR_MAX, "%x", 16);

	TEST(StrOfShort, SHRT_MIN, "%d", 10);
	TEST(StrOfShort, SHRT_MAX, "%d", 10);
	TEST(StrOfUShort, USHRT_MAX, "%u", 10);
	TEST(StrOfUShort, USHRT_MAX, "%o", 8);
	TEST(StrOfUShort, USHRT_MAX, "%x", 16);

	TEST(StrOfInt, INT_MIN, "%d", 10);
	TEST(StrOfInt, INT_MAX, "%d", 10);
	TEST(StrOfUInt, UINT_MAX, "%u", 10);
	TEST(StrOfUInt, UINT_MAX, "%o", 8);
	TEST(StrOfUInt, UINT_MAX, "%x", 16);

	TEST(StrOfLong, LONG_MIN, "%ld", 10);
	TEST(StrOfLong, LONG_MAX, "%ld", 10);
	TEST(StrOfULong, ULONG_MAX, "%lu", 10);
	TEST(StrOfULong, ULONG_MAX, "%lo", 8);
	TEST(StrOfULong, ULONG_MAX, "%lx", 16);

	TEST(StrOfSMax, SMAX_MIN, SMAX_PRI, 10);
	TEST(StrOfSMax, SMAX_MAX, SMAX_PRI, 10);
	TEST(StrOfUMax, UMAX_MAX, UMAX_PRI, 10);
	TEST(StrOfUMax, UMAX_MAX, UMAX_PRIo, 8);
	TEST(StrOfUMax, UMAX_MAX, UMAX_PRIx, 16);
}

static void TestError(void)
{
	int ret; char c;
	ret = StrOfInt(NULL, 1, 1, 10);
	assert(ret == StrOfInt_errBadArg);
	ret = StrOfInt(&c, 0, 1, 10);
	assert(ret == StrOfInt_errBufBoom);
	ret = StrOfInt(&c, 1, 1, 0);
	assert(ret == StrOfInt_errBadArg);
	ret = StrOfInt(&c, 1, 1, 10);
	assert(ret == 1 && c == '1');
}

static void TestMidStr(void)
{
	char sz[99]; sprintf(sz, "Hello 0000!");
	StrOfUInt(&sz[6], 4, 2018, 10);
	assert(strcmp(sz, "Hello 2018!") == 0);
}

static void TestCalcLen(void)
{
	assert(StrOfUInt(NULL, 0, 0, 10) == 1);
	assert(StrOfInt(NULL, 0, -123, 10) == 4);
	assert(StrOfUInt(NULL, 0, 65535, 10) == 5);
	assert(StrOfULong(NULL, 0, 0xff0ff1ce, 16) == 8);
}

int main(void)
{
	TestError();
	TestCalcLen();
	TestMidStr();
	TestEdgeCases();
	return 0;
}
