<शैली गुरु>
/*
 * Implement primitive पुनः_स्मृति(3) functionality.
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * 2006 (c) MontaVista, Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "page.h"
#समावेश "string.h"
#समावेश "ops.h"

#घोषणा	ENTRY_BEEN_USED	0x01
#घोषणा	ENTRY_IN_USE	0x02

अटल काष्ठा alloc_info अणु
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	base;
	अचिन्हित दीर्घ	size;
पूर्ण *alloc_tbl;

अटल अचिन्हित दीर्घ tbl_entries;
अटल अचिन्हित दीर्घ alloc_min;
अटल अचिन्हित दीर्घ next_base;
अटल अचिन्हित दीर्घ space_left;

/*
 * First समय an entry is used, its base and size are set.
 * An entry can be मुक्तd and re-दो_स्मृति'd but its base & size don't change.
 * Should be smart enough क्रम needs of bootwrapper.
 */
अटल व्योम *simple_दो_स्मृति(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा alloc_info *p = alloc_tbl;

	अगर (size == 0)
		जाओ err_out;

	size = _ALIGN_UP(size, alloc_min);

	क्रम (i=0; i<tbl_entries; i++, p++)
		अगर (!(p->flags & ENTRY_BEEN_USED)) अणु /* never been used */
			अगर (size <= space_left) अणु
				p->base = next_base;
				p->size = size;
				p->flags = ENTRY_BEEN_USED | ENTRY_IN_USE;
				next_base += size;
				space_left -= size;
				वापस (व्योम *)p->base;
			पूर्ण
			जाओ err_out; /* not enough space left */
		पूर्ण
		/* reuse an entry keeping same base & size */
		अन्यथा अगर (!(p->flags & ENTRY_IN_USE) && (size <= p->size)) अणु
			p->flags |= ENTRY_IN_USE;
			वापस (व्योम *)p->base;
		पूर्ण
err_out:
	वापस शून्य;
पूर्ण

अटल काष्ठा alloc_info *simple_find_entry(व्योम *ptr)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा alloc_info *p = alloc_tbl;

	क्रम (i=0; i<tbl_entries; i++,p++) अणु
		अगर (!(p->flags & ENTRY_BEEN_USED))
			अवरोध;
		अगर ((p->flags & ENTRY_IN_USE) &&
		    (p->base == (अचिन्हित दीर्घ)ptr))
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम simple_मुक्त(व्योम *ptr)
अणु
	काष्ठा alloc_info *p = simple_find_entry(ptr);

	अगर (p != शून्य)
		p->flags &= ~ENTRY_IN_USE;
पूर्ण

/*
 * Change size of area poपूर्णांकed to by 'ptr' to 'size'.
 * If 'ptr' is NULL, then its a malloc().  If 'size' is 0, then its a मुक्त().
 * 'ptr' must be शून्य or a poपूर्णांकer to a non-मुक्तd area previously वापसed by
 * simple_पुनः_स्मृति() or simple_दो_स्मृति().
 */
अटल व्योम *simple_पुनः_स्मृति(व्योम *ptr, अचिन्हित दीर्घ size)
अणु
	काष्ठा alloc_info *p;
	व्योम *new;

	अगर (size == 0) अणु
		simple_मुक्त(ptr);
		वापस शून्य;
	पूर्ण

	अगर (ptr == शून्य)
		वापस simple_दो_स्मृति(size);

	p = simple_find_entry(ptr);
	अगर (p == शून्य) /* ptr not from simple_दो_स्मृति/simple_पुनः_स्मृति */
		वापस शून्य;
	अगर (size <= p->size) /* fits in current block */
		वापस ptr;

	new = simple_दो_स्मृति(size);
	स_नकल(new, ptr, p->size);
	simple_मुक्त(ptr);
	वापस new;
पूर्ण

/*
 * Returns addr of first byte after heap so caller can see अगर it took
 * too much space.  If so, change args & try again.
 */
व्योम *simple_alloc_init(अक्षर *base, अचिन्हित दीर्घ heap_size,
			अचिन्हित दीर्घ granularity, अचिन्हित दीर्घ max_allocs)
अणु
	अचिन्हित दीर्घ heap_base, tbl_size;

	heap_size = _ALIGN_UP(heap_size, granularity);
	alloc_min = granularity;
	tbl_entries = max_allocs;

	tbl_size = tbl_entries * माप(काष्ठा alloc_info);

	alloc_tbl = (काष्ठा alloc_info *)_ALIGN_UP((अचिन्हित दीर्घ)base, 8);
	स_रखो(alloc_tbl, 0, tbl_size);

	heap_base = _ALIGN_UP((अचिन्हित दीर्घ)alloc_tbl + tbl_size, alloc_min);

	next_base = heap_base;
	space_left = heap_size;

	platक्रमm_ops.दो_स्मृति = simple_दो_स्मृति;
	platक्रमm_ops.मुक्त = simple_मुक्त;
	platक्रमm_ops.पुनः_स्मृति = simple_पुनः_स्मृति;

	वापस (व्योम *)(heap_base + heap_size);
पूर्ण
