<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * jitdump.h: jitted code info encapsulation file क्रमmat
 *
 * Adapted from OProfile GPLv2 support jidump.h:
 * Copyright 2007 OProfile authors
 * Jens Wilke
 * Daniel Hansel
 * Copyright IBM Corporation 2007
 */
#अगर_अघोषित JITDUMP_H
#घोषणा JITDUMP_H

#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <मानक_निवेशt.h>

/* JiTD */
#घोषणा JITHEADER_MAGIC		0x4A695444
#घोषणा JITHEADER_MAGIC_SW	0x4454694A

#घोषणा PADDING_8ALIGNED(x) ((((x) + 7) & 7) ^ 7)
#घोषणा ALIGN_8(x) (((x) + 7) & (~7))

#घोषणा JITHEADER_VERSION 1

क्रमागत jitdump_flags_bits अणु
	JITDUMP_FLAGS_ARCH_TIMESTAMP_BIT,
	JITDUMP_FLAGS_MAX_BIT,
पूर्ण;

#घोषणा JITDUMP_FLAGS_ARCH_TIMESTAMP	(1ULL << JITDUMP_FLAGS_ARCH_TIMESTAMP_BIT)

#घोषणा JITDUMP_FLAGS_RESERVED (JITDUMP_FLAGS_MAX_BIT < 64 ? \
				(~((1ULL << JITDUMP_FLAGS_MAX_BIT) - 1)) : 0)

काष्ठा jitheader अणु
	uपूर्णांक32_t magic;		/* अक्षरacters "jItD" */
	uपूर्णांक32_t version;	/* header version */
	uपूर्णांक32_t total_size;	/* total size of header */
	uपूर्णांक32_t elf_mach;	/* elf mach target */
	uपूर्णांक32_t pad1;		/* reserved */
	uपूर्णांक32_t pid;		/* JIT process id */
	uपूर्णांक64_t बारtamp;	/* बारtamp */
	uपूर्णांक64_t flags;		/* flags */
पूर्ण;

क्रमागत jit_record_type अणु
	JIT_CODE_LOAD		= 0,
        JIT_CODE_MOVE           = 1,
	JIT_CODE_DEBUG_INFO	= 2,
	JIT_CODE_CLOSE		= 3,
	JIT_CODE_UNWINDING_INFO	= 4,

	JIT_CODE_MAX,
पूर्ण;

/* record prefix (mandatory in each record) */
काष्ठा jr_prefix अणु
	uपूर्णांक32_t id;
	uपूर्णांक32_t total_size;
	uपूर्णांक64_t बारtamp;
पूर्ण;

काष्ठा jr_code_load अणु
	काष्ठा jr_prefix p;

	uपूर्णांक32_t pid;
	uपूर्णांक32_t tid;
	uपूर्णांक64_t vma;
	uपूर्णांक64_t code_addr;
	uपूर्णांक64_t code_size;
	uपूर्णांक64_t code_index;
पूर्ण;

काष्ठा jr_code_बंद अणु
	काष्ठा jr_prefix p;
पूर्ण;

काष्ठा jr_code_move अणु
	काष्ठा jr_prefix p;

	uपूर्णांक32_t pid;
	uपूर्णांक32_t tid;
	uपूर्णांक64_t vma;
	uपूर्णांक64_t old_code_addr;
	uपूर्णांक64_t new_code_addr;
	uपूर्णांक64_t code_size;
	uपूर्णांक64_t code_index;
पूर्ण;

काष्ठा debug_entry अणु
	uपूर्णांक64_t addr;
	पूर्णांक lineno;	    /* source line number starting at 1 */
	पूर्णांक discrim;	    /* column discriminator, 0 is शेष */
	स्थिर अक्षर name[]; /* null terminated filename, \षff\0 अगर same as previous entry */
पूर्ण;

काष्ठा jr_code_debug_info अणु
	काष्ठा jr_prefix p;

	uपूर्णांक64_t code_addr;
	uपूर्णांक64_t nr_entry;
	काष्ठा debug_entry entries[];
पूर्ण;

काष्ठा jr_code_unwinding_info अणु
	काष्ठा jr_prefix p;

	uपूर्णांक64_t unwinding_size;
	uपूर्णांक64_t eh_frame_hdr_size;
	uपूर्णांक64_t mapped_size;
	स्थिर अक्षर unwinding_data[];
पूर्ण;

जोड़ jr_entry अणु
        काष्ठा jr_code_debug_info info;
        काष्ठा jr_code_बंद बंद;
        काष्ठा jr_code_load load;
        काष्ठा jr_code_move move;
        काष्ठा jr_prefix prefix;
        काष्ठा jr_code_unwinding_info unwinding;
पूर्ण;

अटल अंतरभूत काष्ठा debug_entry *
debug_entry_next(काष्ठा debug_entry *ent)
अणु
	व्योम *a = ent + 1;
	माप_प्रकार l = म_माप(ent->name) + 1;
	वापस a + l;
पूर्ण

अटल अंतरभूत अक्षर *
debug_entry_file(काष्ठा debug_entry *ent)
अणु
	व्योम *a = ent + 1;
	वापस a;
पूर्ण

#पूर्ण_अगर /* !JITDUMP_H */
