<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_MEM_DETECT_H
#घोषणा _ASM_S390_MEM_DETECT_H

#समावेश <linux/types.h>

क्रमागत mem_info_source अणु
	MEM_DETECT_NONE = 0,
	MEM_DETECT_SCLP_STOR_INFO,
	MEM_DETECT_DIAG260,
	MEM_DETECT_SCLP_READ_INFO,
	MEM_DETECT_BIN_SEARCH
पूर्ण;

काष्ठा mem_detect_block अणु
	u64 start;
	u64 end;
पूर्ण;

/*
 * Storage element id is defined as 1 byte (up to 256 storage elements).
 * In practise only storage element id 0 and 1 are used).
 * According to architecture one storage element could have as much as
 * 1020 subincrements. 255 mem_detect_blocks are embedded in mem_detect_info.
 * If more mem_detect_blocks are required, a block of memory from alपढ़ोy
 * known mem_detect_block is taken (entries_extended poपूर्णांकs to it).
 */
#घोषणा MEM_INLINED_ENTRIES 255 /* (PAGE_SIZE - 16) / 16 */

काष्ठा mem_detect_info अणु
	u32 count;
	u8 info_source;
	काष्ठा mem_detect_block entries[MEM_INLINED_ENTRIES];
	काष्ठा mem_detect_block *entries_extended;
पूर्ण;
बाह्य काष्ठा mem_detect_info mem_detect;

व्योम add_mem_detect_block(u64 start, u64 end);

अटल अंतरभूत पूर्णांक __get_mem_detect_block(u32 n, अचिन्हित दीर्घ *start,
					 अचिन्हित दीर्घ *end)
अणु
	अगर (n >= mem_detect.count) अणु
		*start = 0;
		*end = 0;
		वापस -1;
	पूर्ण

	अगर (n < MEM_INLINED_ENTRIES) अणु
		*start = (अचिन्हित दीर्घ)mem_detect.entries[n].start;
		*end = (अचिन्हित दीर्घ)mem_detect.entries[n].end;
	पूर्ण अन्यथा अणु
		*start = (अचिन्हित दीर्घ)mem_detect.entries_extended[n - MEM_INLINED_ENTRIES].start;
		*end = (अचिन्हित दीर्घ)mem_detect.entries_extended[n - MEM_INLINED_ENTRIES].end;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * क्रम_each_mem_detect_block - early online memory range iterator
 * @i: an पूर्णांकeger used as loop variable
 * @p_start: ptr to अचिन्हित दीर्घ क्रम start address of the range
 * @p_end: ptr to अचिन्हित दीर्घ क्रम end address of the range
 *
 * Walks over detected online memory ranges.
 */
#घोषणा क्रम_each_mem_detect_block(i, p_start, p_end)			\
	क्रम (i = 0, __get_mem_detect_block(i, p_start, p_end);		\
	     i < mem_detect.count;					\
	     i++, __get_mem_detect_block(i, p_start, p_end))

अटल अंतरभूत व्योम get_mem_detect_reserved(अचिन्हित दीर्घ *start,
					   अचिन्हित दीर्घ *size)
अणु
	*start = (अचिन्हित दीर्घ)mem_detect.entries_extended;
	अगर (mem_detect.count > MEM_INLINED_ENTRIES)
		*size = (mem_detect.count - MEM_INLINED_ENTRIES) * माप(काष्ठा mem_detect_block);
	अन्यथा
		*size = 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_mem_detect_end(व्योम)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;

	अगर (mem_detect.count) अणु
		__get_mem_detect_block(mem_detect.count - 1, &start, &end);
		वापस end;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर
