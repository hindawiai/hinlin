<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__A_OUT_GNU_H__
#घोषणा _UAPI__A_OUT_GNU_H__

#घोषणा __GNU_EXEC_MACROS__

#अगर_अघोषित __STRUCT_EXEC_OVERRIDE__

#समावेश <यंत्र/a.out.h>

#पूर्ण_अगर /* __STRUCT_EXEC_OVERRIDE__ */

#अगर_अघोषित __ASSEMBLY__

/* these go in the N_MACHTYPE field */
क्रमागत machine_type अणु
#अगर defined (M_OLDSUN2)
  M__OLDSUN2 = M_OLDSUN2,
#अन्यथा
  M_OLDSUN2 = 0,
#पूर्ण_अगर
#अगर defined (M_68010)
  M__68010 = M_68010,
#अन्यथा
  M_68010 = 1,
#पूर्ण_अगर
#अगर defined (M_68020)
  M__68020 = M_68020,
#अन्यथा
  M_68020 = 2,
#पूर्ण_अगर
#अगर defined (M_SPARC)
  M__SPARC = M_SPARC,
#अन्यथा
  M_SPARC = 3,
#पूर्ण_अगर
  /* skip a bunch so we करोn't run into any of sun's numbers */
  M_386 = 100,
  M_MIPS1 = 151,	/* MIPS R3000/R3000 binary */
  M_MIPS2 = 152		/* MIPS R6000/R4000 binary */
पूर्ण;

#अगर !defined (N_MAGIC)
#घोषणा N_MAGIC(exec) ((exec).a_info & 0xffff)
#पूर्ण_अगर
#घोषणा N_MACHTYPE(exec) ((क्रमागत machine_type)(((exec).a_info >> 16) & 0xff))
#घोषणा N_FLAGS(exec) (((exec).a_info >> 24) & 0xff)
#घोषणा N_SET_INFO(exec, magic, type, flags) \
	((exec).a_info = ((magic) & 0xffff) \
	 | (((पूर्णांक)(type) & 0xff) << 16) \
	 | (((flags) & 0xff) << 24))
#घोषणा N_SET_MAGIC(exec, magic) \
	((exec).a_info = (((exec).a_info & 0xffff0000) | ((magic) & 0xffff)))

#घोषणा N_SET_MACHTYPE(exec, machtype) \
	((exec).a_info = \
	 ((exec).a_info&0xff00ffff) | ((((पूर्णांक)(machtype))&0xff) << 16))

#घोषणा N_SET_FLAGS(exec, flags) \
	((exec).a_info = \
	 ((exec).a_info&0x00ffffff) | (((flags) & 0xff) << 24))

/* Code indicating object file or impure executable.  */
#घोषणा OMAGIC 0407
/* Code indicating pure executable.  */
#घोषणा NMAGIC 0410
/* Code indicating demand-paged executable.  */
#घोषणा ZMAGIC 0413
/* This indicates a demand-paged executable with the header in the text. 
   The first page is unmapped to help trap शून्य poपूर्णांकer references */
#घोषणा QMAGIC 0314

/* Code indicating core file.  */
#घोषणा CMAGIC 0421

#अगर !defined (N_BADMAG)
#घोषणा N_BADMAG(x)	  (N_MAGIC(x) != OMAGIC		\
			&& N_MAGIC(x) != NMAGIC		\
  			&& N_MAGIC(x) != ZMAGIC \
		        && N_MAGIC(x) != QMAGIC)
#पूर्ण_अगर

#घोषणा _N_HDROFF(x) (1024 - माप (काष्ठा exec))

#अगर !defined (N_TXTOFF)
#घोषणा N_TXTOFF(x) \
 (N_MAGIC(x) == ZMAGIC ? _N_HDROFF((x)) + माप (काष्ठा exec) : \
  (N_MAGIC(x) == QMAGIC ? 0 : माप (काष्ठा exec)))
#पूर्ण_अगर

#अगर !defined (N_DATOFF)
#घोषणा N_DATOFF(x) (N_TXTOFF(x) + (x).a_text)
#पूर्ण_अगर

#अगर !defined (N_TRELOFF)
#घोषणा N_TRELOFF(x) (N_DATOFF(x) + (x).a_data)
#पूर्ण_अगर

#अगर !defined (N_DRELOFF)
#घोषणा N_DRELOFF(x) (N_TRELOFF(x) + N_TRSIZE(x))
#पूर्ण_अगर

#अगर !defined (N_SYMOFF)
#घोषणा N_SYMOFF(x) (N_DRELOFF(x) + N_DRSIZE(x))
#पूर्ण_अगर

#अगर !defined (N_STROFF)
#घोषणा N_STROFF(x) (N_SYMOFF(x) + N_SYMSIZE(x))
#पूर्ण_अगर

/* Address of text segment in memory after it is loaded.  */
#अगर !defined (N_TXTADDR)
#घोषणा N_TXTADDR(x) (N_MAGIC(x) == QMAGIC ? PAGE_SIZE : 0)
#पूर्ण_अगर

/* Address of data segment in memory after it is loaded. */
#अगर_अघोषित __KERNEL__
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर defined(__i386__) || defined(__mc68000__)
#घोषणा SEGMENT_SIZE	1024
#अन्यथा
#अगर_अघोषित SEGMENT_SIZE
#अगर_अघोषित __KERNEL__
#घोषणा SEGMENT_SIZE   getpagesize()
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा _N_SEGMENT_ROUND(x) ALIGN(x, SEGMENT_SIZE)

#घोषणा _N_TXTENDADDR(x) (N_TXTADDR(x)+(x).a_text)

#अगर_अघोषित N_DATADDR
#घोषणा N_DATADDR(x) \
    (N_MAGIC(x)==OMAGIC? (_N_TXTENDADDR(x)) \
     : (_N_SEGMENT_ROUND (_N_TXTENDADDR(x))))
#पूर्ण_अगर

/* Address of bss segment in memory after it is loaded.  */
#अगर !defined (N_BSSADDR)
#घोषणा N_BSSADDR(x) (N_DATADDR(x) + (x).a_data)
#पूर्ण_अगर

#अगर !defined (N_NLIST_DECLARED)
काष्ठा nlist अणु
  जोड़ अणु
    अक्षर *n_name;
    काष्ठा nlist *n_next;
    दीर्घ n_strx;
  पूर्ण n_un;
  अचिन्हित अक्षर n_type;
  अक्षर n_other;
  लघु n_desc;
  अचिन्हित दीर्घ n_value;
पूर्ण;
#पूर्ण_अगर /* no N_NLIST_DECLARED.  */

#अगर !defined (N_UNDF)
#घोषणा N_UNDF 0
#पूर्ण_अगर
#अगर !defined (N_ABS)
#घोषणा N_ABS 2
#पूर्ण_अगर
#अगर !defined (N_TEXT)
#घोषणा N_TEXT 4
#पूर्ण_अगर
#अगर !defined (N_DATA)
#घोषणा N_DATA 6
#पूर्ण_अगर
#अगर !defined (N_BSS)
#घोषणा N_BSS 8
#पूर्ण_अगर
#अगर !defined (N_FN)
#घोषणा N_FN 15
#पूर्ण_अगर

#अगर !defined (N_EXT)
#घोषणा N_EXT 1
#पूर्ण_अगर
#अगर !defined (N_TYPE)
#घोषणा N_TYPE 036
#पूर्ण_अगर
#अगर !defined (N_STAB)
#घोषणा N_STAB 0340
#पूर्ण_अगर

/* The following type indicates the definition of a symbol as being
   an indirect reference to another symbol.  The other symbol
   appears as an undefined reference, immediately following this symbol.

   Indirection is asymmetrical.  The other symbol's value will be used
   to satisfy requests क्रम the indirect symbol, but not vice versa.
   If the other symbol करोes not have a definition, libraries will
   be searched to find a definition.  */
#घोषणा N_INDR 0xa

/* The following symbols refer to set elements.
   All the N_SET[ATDB] symbols with the same name क्रमm one set.
   Space is allocated क्रम the set in the text section, and each set
   element's value is stored पूर्णांकo one word of the space.
   The first word of the space is the length of the set (number of elements).

   The address of the set is made पूर्णांकo an N_SETV symbol
   whose name is the same as the name of the set.
   This symbol acts like a N_DATA global symbol
   in that it can satisfy undefined बाह्यal references.  */

/* These appear as input to LD, in a .o file.  */
#घोषणा	N_SETA	0x14		/* Absolute set element symbol */
#घोषणा	N_SETT	0x16		/* Text set element symbol */
#घोषणा	N_SETD	0x18		/* Data set element symbol */
#घोषणा	N_SETB	0x1A		/* Bss set element symbol */

/* This is output from LD.  */
#घोषणा N_SETV	0x1C		/* Poपूर्णांकer to set vector in data area.  */

#अगर !defined (N_RELOCATION_INFO_DECLARED)
/* This काष्ठाure describes a single relocation to be perक्रमmed.
   The text-relocation section of the file is a vector of these काष्ठाures,
   all of which apply to the text section.
   Likewise, the data-relocation section applies to the data section.  */

काष्ठा relocation_info
अणु
  /* Address (within segment) to be relocated.  */
  पूर्णांक r_address;
  /* The meaning of r_symbolnum depends on r_बाह्य.  */
  अचिन्हित पूर्णांक r_symbolnum:24;
  /* Nonzero means value is a pc-relative offset
     and it should be relocated क्रम changes in its own address
     as well as क्रम changes in the symbol or section specअगरied.  */
  अचिन्हित पूर्णांक r_pcrel:1;
  /* Length (as exponent of 2) of the field to be relocated.
     Thus, a value of 2 indicates 1<<2 bytes.  */
  अचिन्हित पूर्णांक r_length:2;
  /* 1 => relocate with value of symbol.
          r_symbolnum is the index of the symbol
	  in file's the symbol table.
     0 => relocate with the address of a segment.
          r_symbolnum is N_TEXT, N_DATA, N_BSS or N_ABS
	  (the N_EXT bit may be set also, but signअगरies nothing).  */
  अचिन्हित पूर्णांक r_बाह्य:1;
  /* Four bits that aren't used, but when writing an object file
     it is desirable to clear them.  */
  अचिन्हित पूर्णांक r_pad:4;
पूर्ण;
#पूर्ण_अगर /* no N_RELOCATION_INFO_DECLARED.  */

#पूर्ण_अगर /*__ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI__A_OUT_GNU_H__ */
