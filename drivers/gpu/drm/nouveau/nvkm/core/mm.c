<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश <core/mm.h>

#घोषणा node(root, dir) ((root)->nl_entry.dir == &mm->nodes) ? शून्य :          \
	list_entry((root)->nl_entry.dir, काष्ठा nvkm_mm_node, nl_entry)

व्योम
nvkm_mm_dump(काष्ठा nvkm_mm *mm, स्थिर अक्षर *header)
अणु
	काष्ठा nvkm_mm_node *node;

	pr_err("nvkm: %s\n", header);
	pr_err("nvkm: node list:\n");
	list_क्रम_each_entry(node, &mm->nodes, nl_entry) अणु
		pr_err("nvkm: \t%08x %08x %d\n",
		       node->offset, node->length, node->type);
	पूर्ण
	pr_err("nvkm: free list:\n");
	list_क्रम_each_entry(node, &mm->मुक्त, fl_entry) अणु
		pr_err("nvkm: \t%08x %08x %d\n",
		       node->offset, node->length, node->type);
	पूर्ण
पूर्ण

व्योम
nvkm_mm_मुक्त(काष्ठा nvkm_mm *mm, काष्ठा nvkm_mm_node **pthis)
अणु
	काष्ठा nvkm_mm_node *this = *pthis;

	अगर (this) अणु
		काष्ठा nvkm_mm_node *prev = node(this, prev);
		काष्ठा nvkm_mm_node *next = node(this, next);

		अगर (prev && prev->type == NVKM_MM_TYPE_NONE) अणु
			prev->length += this->length;
			list_del(&this->nl_entry);
			kमुक्त(this); this = prev;
		पूर्ण

		अगर (next && next->type == NVKM_MM_TYPE_NONE) अणु
			next->offset  = this->offset;
			next->length += this->length;
			अगर (this->type == NVKM_MM_TYPE_NONE)
				list_del(&this->fl_entry);
			list_del(&this->nl_entry);
			kमुक्त(this); this = शून्य;
		पूर्ण

		अगर (this && this->type != NVKM_MM_TYPE_NONE) अणु
			list_क्रम_each_entry(prev, &mm->मुक्त, fl_entry) अणु
				अगर (this->offset < prev->offset)
					अवरोध;
			पूर्ण

			list_add_tail(&this->fl_entry, &prev->fl_entry);
			this->type = NVKM_MM_TYPE_NONE;
		पूर्ण
	पूर्ण

	*pthis = शून्य;
पूर्ण

अटल काष्ठा nvkm_mm_node *
region_head(काष्ठा nvkm_mm *mm, काष्ठा nvkm_mm_node *a, u32 size)
अणु
	काष्ठा nvkm_mm_node *b;

	अगर (a->length == size)
		वापस a;

	b = kदो_स्मृति(माप(*b), GFP_KERNEL);
	अगर (unlikely(b == शून्य))
		वापस शून्य;

	b->offset = a->offset;
	b->length = size;
	b->heap   = a->heap;
	b->type   = a->type;
	a->offset += size;
	a->length -= size;
	list_add_tail(&b->nl_entry, &a->nl_entry);
	अगर (b->type == NVKM_MM_TYPE_NONE)
		list_add_tail(&b->fl_entry, &a->fl_entry);

	वापस b;
पूर्ण

पूर्णांक
nvkm_mm_head(काष्ठा nvkm_mm *mm, u8 heap, u8 type, u32 size_max, u32 size_min,
	     u32 align, काष्ठा nvkm_mm_node **pnode)
अणु
	काष्ठा nvkm_mm_node *prev, *this, *next;
	u32 mask = align - 1;
	u32 splitoff;
	u32 s, e;

	BUG_ON(type == NVKM_MM_TYPE_NONE || type == NVKM_MM_TYPE_HOLE);

	list_क्रम_each_entry(this, &mm->मुक्त, fl_entry) अणु
		अगर (unlikely(heap != NVKM_MM_HEAP_ANY)) अणु
			अगर (this->heap != heap)
				जारी;
		पूर्ण
		e = this->offset + this->length;
		s = this->offset;

		prev = node(this, prev);
		अगर (prev && prev->type != type)
			s = roundup(s, mm->block_size);

		next = node(this, next);
		अगर (next && next->type != type)
			e = roundकरोwn(e, mm->block_size);

		s  = (s + mask) & ~mask;
		e &= ~mask;
		अगर (s > e || e - s < size_min)
			जारी;

		splitoff = s - this->offset;
		अगर (splitoff && !region_head(mm, this, splitoff))
			वापस -ENOMEM;

		this = region_head(mm, this, min(size_max, e - s));
		अगर (!this)
			वापस -ENOMEM;

		this->next = शून्य;
		this->type = type;
		list_del(&this->fl_entry);
		*pnode = this;
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल काष्ठा nvkm_mm_node *
region_tail(काष्ठा nvkm_mm *mm, काष्ठा nvkm_mm_node *a, u32 size)
अणु
	काष्ठा nvkm_mm_node *b;

	अगर (a->length == size)
		वापस a;

	b = kदो_स्मृति(माप(*b), GFP_KERNEL);
	अगर (unlikely(b == शून्य))
		वापस शून्य;

	a->length -= size;
	b->offset  = a->offset + a->length;
	b->length  = size;
	b->heap    = a->heap;
	b->type    = a->type;

	list_add(&b->nl_entry, &a->nl_entry);
	अगर (b->type == NVKM_MM_TYPE_NONE)
		list_add(&b->fl_entry, &a->fl_entry);

	वापस b;
पूर्ण

पूर्णांक
nvkm_mm_tail(काष्ठा nvkm_mm *mm, u8 heap, u8 type, u32 size_max, u32 size_min,
	     u32 align, काष्ठा nvkm_mm_node **pnode)
अणु
	काष्ठा nvkm_mm_node *prev, *this, *next;
	u32 mask = align - 1;

	BUG_ON(type == NVKM_MM_TYPE_NONE || type == NVKM_MM_TYPE_HOLE);

	list_क्रम_each_entry_reverse(this, &mm->मुक्त, fl_entry) अणु
		u32 e = this->offset + this->length;
		u32 s = this->offset;
		u32 c = 0, a;
		अगर (unlikely(heap != NVKM_MM_HEAP_ANY)) अणु
			अगर (this->heap != heap)
				जारी;
		पूर्ण

		prev = node(this, prev);
		अगर (prev && prev->type != type)
			s = roundup(s, mm->block_size);

		next = node(this, next);
		अगर (next && next->type != type) अणु
			e = roundकरोwn(e, mm->block_size);
			c = next->offset - e;
		पूर्ण

		s = (s + mask) & ~mask;
		a = e - s;
		अगर (s > e || a < size_min)
			जारी;

		a  = min(a, size_max);
		s  = (e - a) & ~mask;
		c += (e - s) - a;

		अगर (c && !region_tail(mm, this, c))
			वापस -ENOMEM;

		this = region_tail(mm, this, a);
		अगर (!this)
			वापस -ENOMEM;

		this->next = शून्य;
		this->type = type;
		list_del(&this->fl_entry);
		*pnode = this;
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

पूर्णांक
nvkm_mm_init(काष्ठा nvkm_mm *mm, u8 heap, u32 offset, u32 length, u32 block)
अणु
	काष्ठा nvkm_mm_node *node, *prev;
	u32 next;

	अगर (nvkm_mm_initialised(mm)) अणु
		prev = list_last_entry(&mm->nodes, typeof(*node), nl_entry);
		next = prev->offset + prev->length;
		अगर (next != offset) अणु
			BUG_ON(next > offset);
			अगर (!(node = kzalloc(माप(*node), GFP_KERNEL)))
				वापस -ENOMEM;
			node->type   = NVKM_MM_TYPE_HOLE;
			node->offset = next;
			node->length = offset - next;
			list_add_tail(&node->nl_entry, &mm->nodes);
		पूर्ण
		BUG_ON(block != mm->block_size);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&mm->nodes);
		INIT_LIST_HEAD(&mm->मुक्त);
		mm->block_size = block;
		mm->heap_nodes = 0;
	पूर्ण

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	अगर (length) अणु
		node->offset  = roundup(offset, mm->block_size);
		node->length  = roundकरोwn(offset + length, mm->block_size);
		node->length -= node->offset;
	पूर्ण

	list_add_tail(&node->nl_entry, &mm->nodes);
	list_add_tail(&node->fl_entry, &mm->मुक्त);
	node->heap = heap;
	mm->heap_nodes++;
	वापस 0;
पूर्ण

पूर्णांक
nvkm_mm_fini(काष्ठा nvkm_mm *mm)
अणु
	काष्ठा nvkm_mm_node *node, *temp;
	पूर्णांक nodes = 0;

	अगर (!nvkm_mm_initialised(mm))
		वापस 0;

	list_क्रम_each_entry(node, &mm->nodes, nl_entry) अणु
		अगर (node->type != NVKM_MM_TYPE_HOLE) अणु
			अगर (++nodes > mm->heap_nodes) अणु
				nvkm_mm_dump(mm, "mm not clean!");
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(node, temp, &mm->nodes, nl_entry) अणु
		list_del(&node->nl_entry);
		kमुक्त(node);
	पूर्ण

	mm->heap_nodes = 0;
	वापस 0;
पूर्ण
