/************************************************************************/
/*                        The Base Typedef                              */
/************************************************************************/

/* build-in types---start */
typedef signed char			 Xbool;		/* Name: b_  Range: Xtrue or Xfalse */

typedef char				 Xchar;		/* Name: c_  Range decided by compiler: -128~+127 or 0~255 */

typedef wchar_t				 Xwchar;		/* Name: wc_  Range decided by compiler: 0~65535 or -32768~+32767 */

typedef unsigned char		 Xuchar1;	/* Name: u1_  Range: 0~255 */

typedef signed char			 Xichar1;	/* Name: i1_  Range: -128~+127 */

typedef unsigned short		 Xushort2;	/* Name: u2_  Range: 0~65535 */

typedef signed short		 Xishort2;	/* Name: i2_  Range: -32768~+32767 */

typedef unsigned int		 Xuint4;	/* Name: u4_  Range: 0~4,294,967,395 */

typedef signed int			 Xiint4;	/* Name: i4_  Range: -2,147,483,648~+2,147,483,647 */

typedef unsigned long		 Xulong4;	/* Name: u4_  Range:  0~4,294,967,395 */

typedef signed long			 Xilong4;	/* Name: i4_  Range: -2,147,483,648~+2,147,483,647 */

typedef unsigned long long	 Xulonglong8;/* Name: u8_  Range: 0~ */

typedef signed long long	 Xilonglong8;/* Name: i8_  Range: -9,223,372,036,854,775,808~+9,223,372,036,854,775,807 */

typedef float				 Xfloat4;	/* Name: f4_  Range: 10^(-37)~10^(38) */

typedef double				 Xdouble8;	/* Name: d8_  Range: 10^(-307)~10^(308) */

typedef long double			 Xdouble16;	/* Name: d16_  Range: 10^(-4831)~10^(4932) */
/* build-in types---end */

/* build-in values---start */

#define Xtrue				 0x01

#define Xfalse				 0x00

#define XT(LS) (L ## LS)
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)

#ifdef __cplusplus
#define XNULL				 0
#else  /* __cplusplus */
#define XNULL				((void *)0)
#endif  /* __cplusplus */

/* build-in values---end */