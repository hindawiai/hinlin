<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MIPSPROM_H
#घोषणा __ASM_MIPSPROM_H

#घोषणा PROM_RESET		0
#घोषणा PROM_EXEC		1
#घोषणा PROM_RESTART		2
#घोषणा PROM_REINIT		3
#घोषणा PROM_REBOOT		4
#घोषणा PROM_AUTOBOOT		5
#घोषणा PROM_OPEN		6
#घोषणा PROM_READ		7
#घोषणा PROM_WRITE		8
#घोषणा PROM_IOCTL		9
#घोषणा PROM_CLOSE		10
#घोषणा PROM_GETCHAR		11
#घोषणा PROM_PUTCHAR		12
#घोषणा PROM_SHOWCHAR		13	/* XXX */
#घोषणा PROM_GETS		14	/* XXX */
#घोषणा PROM_PUTS		15	/* XXX */
#घोषणा PROM_PRINTF		16	/* XXX */

/* What are these क्रम? */
#घोषणा PROM_INITPROTO		17	/* XXX */
#घोषणा PROM_PROTOENABLE	18	/* XXX */
#घोषणा PROM_PROTODISABLE	19	/* XXX */
#घोषणा PROM_GETPKT		20	/* XXX */
#घोषणा PROM_PUTPKT		21	/* XXX */

/* More PROM shit.  Probably has to करो with VME RMW cycles??? */
#घोषणा PROM_ORW_RMW		22	/* XXX */
#घोषणा PROM_ORH_RMW		23	/* XXX */
#घोषणा PROM_ORB_RMW		24	/* XXX */
#घोषणा PROM_ANDW_RMW		25	/* XXX */
#घोषणा PROM_ANDH_RMW		26	/* XXX */
#घोषणा PROM_ANDB_RMW		27	/* XXX */

/* Cache handling stuff */
#घोषणा PROM_FLUSHCACHE		28	/* XXX */
#घोषणा PROM_CLEARCACHE		29	/* XXX */

/* Libc alike stuff */
#घोषणा PROM_SETJMP		30	/* XXX */
#घोषणा PROM_LONGJMP		31	/* XXX */
#घोषणा PROM_BEVUTLB		32	/* XXX */
#घोषणा PROM_GETENV		33	/* XXX */
#घोषणा PROM_SETENV		34	/* XXX */
#घोषणा PROM_ATOB		35	/* XXX */
#घोषणा PROM_STRCMP		36	/* XXX */
#घोषणा PROM_STRLEN		37	/* XXX */
#घोषणा PROM_STRCPY		38	/* XXX */
#घोषणा PROM_STRCAT		39	/* XXX */

/* Misc stuff */
#घोषणा PROM_PARSER		40	/* XXX */
#घोषणा PROM_RANGE		41	/* XXX */
#घोषणा PROM_ARGVIZE		42	/* XXX */
#घोषणा PROM_HELP		43	/* XXX */

/* Entry poपूर्णांकs क्रम some PROM commands */
#घोषणा PROM_DUMPCMD		44	/* XXX */
#घोषणा PROM_SETENVCMD		45	/* XXX */
#घोषणा PROM_UNSETENVCMD	46	/* XXX */
#घोषणा PROM_PRINTENVCMD	47	/* XXX */
#घोषणा PROM_BEVEXCEPT		48	/* XXX */
#घोषणा PROM_ENABLECMD		49	/* XXX */
#घोषणा PROM_DISABLECMD		50	/* XXX */

#घोषणा PROM_CLEARNOFAULT	51	/* XXX */
#घोषणा PROM_NOTIMPLEMENT	52	/* XXX */

#घोषणा PROM_NV_GET		53	/* XXX */
#घोषणा PROM_NV_SET		54	/* XXX */

बाह्य अक्षर *prom_दो_पर्या(अक्षर *);

#पूर्ण_अगर /* __ASM_MIPSPROM_H */
