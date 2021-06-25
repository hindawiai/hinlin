<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ELFNOTE_H
#घोषणा _LINUX_ELFNOTE_H
/*
 * Helper macros to generate ELF Note काष्ठाures, which are put पूर्णांकo a
 * PT_NOTE segment of the final vmlinux image.  These are useful क्रम
 * including name-value pairs of metadata पूर्णांकo the kernel binary (or
 * modules?) क्रम use by बाह्यal programs.
 *
 * Each note has three parts: a name, a type and a desc.  The name is
 * पूर्णांकended to distinguish the note's originator, so it would be a
 * company, project, subप्रणाली, etc; it must be in a suitable क्रमm क्रम
 * use in a section name.  The type is an पूर्णांकeger which is used to tag
 * the data, and is considered to be within the "name" namespace (so
 * "FooCo"'s type 42 is distinct from "BarProj"'s type 42).  The
 * "desc" field is the actual data.  There are no स्थिरraपूर्णांकs on the
 * desc field's contents, though typically they're fairly small.
 *
 * All notes from a given NAME are put पूर्णांकo a section named
 * .note.NAME.  When the kernel image is finally linked, all the notes
 * are packed पूर्णांकo a single .notes section, which is mapped पूर्णांकo the
 * PT_NOTE segment.  Because notes क्रम a given name are grouped पूर्णांकo
 * the same section, they'll all be adjacent the output file.
 *
 * This file defines macros क्रम both C and assembler use.  Their
 * syntax is slightly dअगरferent, but they're semantically similar.
 *
 * See the ELF specअगरication क्रम more detail about ELF notes.
 */

#अगर_घोषित __ASSEMBLER__
/*
 * Generate a काष्ठाure with the same shape as Elfअणु32,64पूर्ण_Nhdr (which
 * turn out to be the same size and shape), followed by the name and
 * desc data with appropriate padding.  The 'desctype' argument is the
 * assembler pseuकरो op defining the type of the data e.g. .asciz जबतक
 * 'descdata' is the data itself e.g.  "hello, world".
 *
 * e.g. ELFNOTE(XYZCo, 42, .asciz, "forty-two")
 *      ELFNOTE(XYZCo, 12, .दीर्घ, 0xdeadbeef)
 */
#घोषणा ELFNOTE_START(name, type, flags)	\
.pushsection .note.name, flags,@note	;	\
  .balign 4				;	\
  .दीर्घ 2f - 1f		/* namesz */	;	\
  .दीर्घ 4484f - 3f	/* descsz */	;	\
  .दीर्घ type				;	\
1:.asciz #name				;	\
2:.balign 4				;	\
3:

#घोषणा ELFNOTE_END				\
4484:.balign 4				;	\
.popsection				;

#घोषणा ELFNOTE(name, type, desc)		\
	ELFNOTE_START(name, type, "a")		\
		desc			;	\
	ELFNOTE_END

#अन्यथा	/* !__ASSEMBLER__ */
#समावेश <uapi/linux/elf.h>
/*
 * Use an anonymous काष्ठाure which matches the shape of
 * Elfअणु32,64पूर्ण_Nhdr, but includes the name and desc data.  The size and
 * type of name and desc depend on the macro arguments.  "name" must
 * be a literal string, and "desc" must be passed by value.  You may
 * only define one note per line, since __LINE__ is used to generate
 * unique symbols.
 */
#घोषणा _ELFNOTE_PASTE(a,b)	a##b
#घोषणा _ELFNOTE(size, name, unique, type, desc)			\
	अटल स्थिर काष्ठा अणु						\
		काष्ठा elf##size##_note _nhdr;				\
		अचिन्हित अक्षर _name[माप(name)]			\
		__attribute__((aligned(माप(Elf##size##_Word))));	\
		typeof(desc) _desc					\
			     __attribute__((aligned(माप(Elf##size##_Word)))); \
	पूर्ण _ELFNOTE_PASTE(_note_, unique)				\
		__used							\
		__attribute__((section(".note." name),			\
			       aligned(माप(Elf##size##_Word)),	\
			       unused)) = अणु				\
		अणु							\
			माप(name),					\
			माप(desc),					\
			type,						\
		पूर्ण,							\
		name,							\
		desc							\
	पूर्ण
#घोषणा ELFNOTE(size, name, type, desc)		\
	_ELFNOTE(size, name, __LINE__, type, desc)

#घोषणा ELFNOTE32(name, type, desc) ELFNOTE(32, name, type, desc)
#घोषणा ELFNOTE64(name, type, desc) ELFNOTE(64, name, type, desc)
#पूर्ण_अगर	/* __ASSEMBLER__ */

#पूर्ण_अगर /* _LINUX_ELFNOTE_H */
