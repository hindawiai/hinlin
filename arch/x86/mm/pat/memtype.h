<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MEMTYPE_H_
#घोषणा __MEMTYPE_H_

बाह्य पूर्णांक pat_debug_enable;

#घोषणा dprपूर्णांकk(fmt, arg...) \
	करो अणु अगर (pat_debug_enable) pr_info("x86/PAT: " fmt, ##arg); पूर्ण जबतक (0)

काष्ठा memtype अणु
	u64			start;
	u64			end;
	u64			subtree_max_end;
	क्रमागत page_cache_mode	type;
	काष्ठा rb_node		rb;
पूर्ण;

अटल अंतरभूत अक्षर *cattr_name(क्रमागत page_cache_mode pcm)
अणु
	चयन (pcm) अणु
	हाल _PAGE_CACHE_MODE_UC:		वापस "uncached";
	हाल _PAGE_CACHE_MODE_UC_MINUS:		वापस "uncached-minus";
	हाल _PAGE_CACHE_MODE_WB:		वापस "write-back";
	हाल _PAGE_CACHE_MODE_WC:		वापस "write-combining";
	हाल _PAGE_CACHE_MODE_WT:		वापस "write-through";
	हाल _PAGE_CACHE_MODE_WP:		वापस "write-protected";
	शेष:				वापस "broken";
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_PAT
बाह्य पूर्णांक memtype_check_insert(काष्ठा memtype *entry_new,
				क्रमागत page_cache_mode *new_type);
बाह्य काष्ठा memtype *memtype_erase(u64 start, u64 end);
बाह्य काष्ठा memtype *memtype_lookup(u64 addr);
बाह्य पूर्णांक memtype_copy_nth_element(काष्ठा memtype *entry_out, loff_t pos);
#अन्यथा
अटल अंतरभूत पूर्णांक memtype_check_insert(काष्ठा memtype *entry_new,
				       क्रमागत page_cache_mode *new_type)
अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा memtype *memtype_erase(u64 start, u64 end)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा memtype *memtype_lookup(u64 addr)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक memtype_copy_nth_element(काष्ठा memtype *out, loff_t pos)
अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MEMTYPE_H_ */
