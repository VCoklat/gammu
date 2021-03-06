/* (c) 2002-2004 by Marcin Wiacek and others */

#ifndef __coding_h
#define __coding_h

#if defined(_MSC_VER) && defined(__cplusplus)
    extern "C" {
#endif

#include <stdlib.h>
#ifdef HAVE_ISWSPACE
#  include <wctype.h>
#endif

#include "../misc.h"

#ifndef HAVE_ISWSPACE
typedef		int wint_t;
#endif

/* ---------------------------- Unicode ------------------------------------ */
bool 		mywstrncasecmp			(unsigned const char *a, unsigned const char *b, int num);
unsigned char	*mywstrstr			(unsigned const char *haystack, unsigned const char *needle);
bool 		mywstrncmp			(unsigned const char *a, unsigned const char *b, int num);
bool 		myiswspace	  		(unsigned const char *src);
#ifndef HAVE_TOWLOWER
int 		towlower			(wchar_t c);
#endif

int		EncodeWithUnicodeAlphabet	(const unsigned char *value, wchar_t *dest);
int		DecodeWithUnicodeAlphabet	(wchar_t value, unsigned char *dest);

size_t		UnicodeLength			(const unsigned char *str);
unsigned char	*DecodeUnicodeString		(const unsigned char *src);
unsigned char   *DecodeUnicodeConsole		(const unsigned char *src);
void		DecodeUnicode			(const unsigned char *src, unsigned char *dest);
void		EncodeUnicode			(unsigned char *dest, const char *src, int len);

void 		CopyUnicodeString		(unsigned char *Dest, unsigned char *Source);
void 		ReverseUnicodeString		(unsigned char *String);

void 		ReadUnicodeFile			(unsigned char *Dest, unsigned char *Source);

void 		DecodeUnicodeSpecialNOKIAChars	(unsigned char *dest, const unsigned char *src, int len);
void 		EncodeUnicodeSpecialNOKIAChars	(unsigned char *dest, const unsigned char *src, int len);

char 		*EncodeUnicodeSpecialChars	(unsigned char *buffer);
char 		*DecodeUnicodeSpecialChars	(unsigned char *buffer);

/* ------------------------------- BCD ------------------------------------- */
unsigned char	EncodeWithBCDAlphabet		(int value);
int		DecodeWithBCDAlphabet		(unsigned char value);

void		DecodeBCD			(unsigned char *dest, const unsigned char *src, int len);
void		EncodeBCD			(unsigned char *dest, const unsigned char *src, int len, bool fill);

/* ------------------------------ UTF7 ------------------------------------- */
void 		DecodeUTF7			(unsigned char *dest, const unsigned char *src, int len);


/* ---------------------------- ISO88591 ----------------------------------- */
void		DecodeISO88591			(unsigned char *dest, const char *src, int len);
void		DecodeISO88591QuotedPrintable	(unsigned char *dest, const unsigned char *src, int len);

/* ------------------------------ UTF8 ------------------------------------- */
int 		EncodeWithUTF8Alphabet2		(unsigned char mychar1, unsigned char mychar2, unsigned char *ret);
int 		DecodeWithUTF8Alphabet2		(unsigned char *src, wchar_t *dest, int len);

bool		EncodeUTF8QuotedPrintable	(unsigned char *dest, const unsigned char *src);
void 		DecodeUTF8QuotedPrintable	(unsigned char *dest, const unsigned char *src, int len);

bool 		EncodeUTF8			(unsigned char *dest, const unsigned char *src);
void 		DecodeUTF8			(unsigned char *dest, const unsigned char *src, int len);

/**
 * Decodes UTF-8 text with XML entities to Unicode.
 */
void DecodeXMLUTF8(unsigned char *dest, const unsigned char *src, int len);

/* ------------------------------- BASE64 ---------------------------------- */
void 		EncodeBASE64			(const unsigned char *Input, unsigned char *Output, int Length);
int 		DecodeBASE64			(const unsigned char *Input, unsigned char *Output, int Length);

/* ----------------------------- HexBin ------------------------------------ */
void		DecodeHexBin			(unsigned char *dest, const unsigned char *src, int len);
void		EncodeHexBin			(unsigned char *dest, const unsigned char *src, int len);

/* ----------------------------- HexUnicode -------------------------------- */
void		DecodeHexUnicode		(unsigned char *dest, const unsigned char *src, int len);
void		EncodeHexUnicode		(unsigned char *dest, const unsigned char *src, int len);

/* ---------------------- DefaultAlphabet for SMS -------------------------- */
void 		EncodeDefault			(unsigned char *dest, const unsigned char *src, int *len, bool UseExtensions, unsigned char *ExtraAlphabet);
void		DecodeDefault			(unsigned char *dest, const unsigned char *src, int len, bool UseExtensions,  unsigned char *ExtraAlphabet);
void 		FindDefaultAlphabetLen		(const unsigned char *src, int *srclen, int *smslen, int maxlen);

int GSM_PackSevenBitsToEight	(int offset, unsigned char *input, unsigned char *output, int length);
int GSM_UnpackEightBitsToSeven	(int offset, int in_length, int out_length,
				 unsigned char *input, unsigned char *output);

/* ----------------- Phone numbers according to GSM specs ------------------ */

/**
 * Enum to handle types of phones numbers like
 * specified in GSM 03.40 section 9.1.2.5
 */
typedef enum {
	/**
	 * Unknown number type
	 */
	NUMBER_UNKNOWN_NUMBERING_PLAN_ISDN		= 0x81,
	/**
	 * International number (full number with code of country)
	 */
	NUMBER_INTERNATIONAL_NUMBERING_PLAN_ISDN	= 0x91,
	/**
	 * Alphanumeric number (with chars too)
	 */
	NUMBER_ALPHANUMERIC_NUMBERING_PLAN_UNKNOWN	= 0xD0

	/* specification give also other values */
} GSM_NumberType;

void		GSM_UnpackSemiOctetNumber	(unsigned char *retval, unsigned char *Number, bool semioctet);
int		GSM_PackSemiOctetNumber		(unsigned char *Number, unsigned char *Output, bool semioctet);

/* ---------------------------- Bits --------------------------------------- */

void BufferAlign      (unsigned char *Destination, int *CurrentBit);
void BufferAlignNumber(int *CurrentBit);

void AddBuffer	  (unsigned char *Destination, int *CurrentBit, unsigned char *Source, int BitsToProcess);
void AddBufferByte(unsigned char *Destination, int *CurrentBit, unsigned char Source, int BitsToProcess);

void GetBuffer    (unsigned char *Source, int *CurrentBit, unsigned char *Destination, int BitsToProcess);
void GetBufferInt (unsigned char *Source, int *CurrentBit, int *integer, int BitsToProcess);
void GetBufferI   (unsigned char *Source, int *CurrentBit, int *result, int BitsToProcess);

int GetBit   (unsigned char *Buffer, int BitNum);
int SetBit   (unsigned char *Buffer, int BitNum);
int ClearBit (unsigned char *Buffer, int BitNum);

/* ---------------------------- Other -------------------------------------- */

void StringToDouble	(char *text, double *d);

#ifndef HAVE_STRNCASECMP
extern int strncasecmp (const char *s1, const char *s2, size_t n);
#endif
#ifndef HAVE_STRCASECMP
extern int strcasecmp (const char *s1, const char *s2);
#endif
#ifndef HAVE_STRCASESTR
extern char *strcasestr(const char *s, const char *find);
#endif
#ifndef HAVE_STRCHRNUL
extern char *strchrnul(char *s, int find);
#endif

void MyGetLine		(unsigned char *Buffer, int *Pos, unsigned char *OutBuffer, int MaxLen, bool MergeLines);

char *EncodeSpecialChars(unsigned char *buffer);
char *DecodeSpecialChars(unsigned char *buffer);

#if defined(_MSC_VER) && defined(__cplusplus)
    }
#endif

#endif

/* How should editor hadle tabs in this file? Add editor commands here.
 * vim: noexpandtab sw=8 ts=8 sts=8:
 */
