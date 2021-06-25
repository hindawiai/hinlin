<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright 1999 Ralf Baechle (ralf@gnu.org)
 * Copyright 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_ARC_TYPES_H
#घोषणा _ASM_ARC_TYPES_H


#अगर_घोषित CONFIG_FW_ARC32

प्रकार अक्षर		CHAR;
प्रकार लघु		SHORT;
प्रकार दीर्घ		LARGE_INTEGER __attribute__ ((__mode__ (__DI__)));
प्रकार दीर्घ		LONG __attribute__ ((__mode__ (__SI__)));
प्रकार अचिन्हित अक्षर	UCHAR;
प्रकार अचिन्हित लघु	USHORT;
प्रकार अचिन्हित दीर्घ	ULONG __attribute__ ((__mode__ (__SI__)));
प्रकार व्योम		VOID;

/* The poपूर्णांकer types.  Note that we're using a 64-bit compiler but all
   poपूर्णांकer in the ARC काष्ठाures are only 32-bit, so we need some disgusting
   workarounds.	 Keep your vomit bag handy.  */
प्रकार LONG		_PCHAR;
प्रकार LONG		_PSHORT;
प्रकार LONG		_PLARGE_INTEGER;
प्रकार LONG		_PLONG;
प्रकार LONG		_PUCHAR;
प्रकार LONG		_PUSHORT;
प्रकार LONG		_PULONG;
प्रकार LONG		_PVOID;

#पूर्ण_अगर /* CONFIG_FW_ARC32 */

#अगर_घोषित CONFIG_FW_ARC64

प्रकार अक्षर		CHAR;
प्रकार लघु		SHORT;
प्रकार दीर्घ		LARGE_INTEGER __attribute__ ((__mode__ (__DI__)));
प्रकार दीर्घ		LONG __attribute__ ((__mode__ (__DI__)));
प्रकार अचिन्हित अक्षर	UCHAR;
प्रकार अचिन्हित लघु	USHORT;
प्रकार अचिन्हित दीर्घ	ULONG __attribute__ ((__mode__ (__DI__)));
प्रकार व्योम		VOID;

/* The poपूर्णांकer types.  We're 64-bit and the firmware is also 64-bit, so
   live is sane ...  */
प्रकार CHAR		*_PCHAR;
प्रकार SHORT		*_PSHORT;
प्रकार LARGE_INTEGER	*_PLARGE_INTEGER;
प्रकार LONG		*_PLONG;
प्रकार UCHAR		*_PUCHAR;
प्रकार USHORT		*_PUSHORT;
प्रकार ULONG		*_PULONG;
प्रकार VOID		*_PVOID;

#पूर्ण_अगर /* CONFIG_FW_ARC64  */

प्रकार CHAR		*PCHAR;
प्रकार SHORT		*PSHORT;
प्रकार LARGE_INTEGER	*PLARGE_INTEGER;
प्रकार LONG		*PLONG;
प्रकार UCHAR		*PUCHAR;
प्रकार USHORT		*PUSHORT;
प्रकार ULONG		*PULONG;
प्रकार VOID		*PVOID;

/*
 * Return type of ArcGetDisplayStatus()
 */
प्रकार काष्ठा अणु
	USHORT	CursorXPosition;
	USHORT	CursorYPosition;
	USHORT	CursorMaxXPosition;
	USHORT	CursorMaxYPosition;
	USHORT	ForegroundColor;
	USHORT	BackgroundColor;
	UCHAR	HighIntensity;
	UCHAR	Underscored;
	UCHAR	ReverseVideo;
पूर्ण DISPLAY_STATUS;

#पूर्ण_अगर /* _ASM_ARC_TYPES_H */
