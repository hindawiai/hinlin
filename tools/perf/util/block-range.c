<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "block-range.h"
#समावेश "annotate.h"
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>

काष्ठा अणु
	काष्ठा rb_root root;
	u64 blocks;
पूर्ण block_ranges;

अटल व्योम block_range__debug(व्योम)
अणु
	/*
	 * XXX still paranoid क्रम now; see अगर we can make this depend on
	 * DEBUG=1 builds.
	 */
#अगर 1
	काष्ठा rb_node *rb;
	u64 old = 0; /* शून्य isn't executable */

	क्रम (rb = rb_first(&block_ranges.root); rb; rb = rb_next(rb)) अणु
		काष्ठा block_range *entry = rb_entry(rb, काष्ठा block_range, node);

		निश्चित(old < entry->start);
		निश्चित(entry->start <= entry->end); /* single inकाष्ठाion block; jump to a jump */

		old = entry->end;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा block_range *block_range__find(u64 addr)
अणु
	काष्ठा rb_node **p = &block_ranges.root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा block_range *entry;

	जबतक (*p != शून्य) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा block_range, node);

		अगर (addr < entry->start)
			p = &parent->rb_left;
		अन्यथा अगर (addr > entry->end)
			p = &parent->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम rb_link_left_of_node(काष्ठा rb_node *left, काष्ठा rb_node *node)
अणु
	काष्ठा rb_node **p = &node->rb_left;
	जबतक (*p) अणु
		node = *p;
		p = &node->rb_right;
	पूर्ण
	rb_link_node(left, node, p);
पूर्ण

अटल अंतरभूत व्योम rb_link_right_of_node(काष्ठा rb_node *right, काष्ठा rb_node *node)
अणु
	काष्ठा rb_node **p = &node->rb_right;
	जबतक (*p) अणु
		node = *p;
		p = &node->rb_left;
	पूर्ण
	rb_link_node(right, node, p);
पूर्ण

/**
 * block_range__create
 * @start: branch target starting this basic block
 * @end:   branch ending this basic block
 *
 * Create all the required block ranges to precisely span the given range.
 */
काष्ठा block_range_iter block_range__create(u64 start, u64 end)
अणु
	काष्ठा rb_node **p = &block_ranges.root.rb_node;
	काष्ठा rb_node *n, *parent = शून्य;
	काष्ठा block_range *next, *entry = शून्य;
	काष्ठा block_range_iter iter = अणु शून्य, शून्य पूर्ण;

	जबतक (*p != शून्य) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा block_range, node);

		अगर (start < entry->start)
			p = &parent->rb_left;
		अन्यथा अगर (start > entry->end)
			p = &parent->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	/*
	 * Didn't find anything.. there's a hole at @start, however @end might
	 * be inside/behind the next range.
	 */
	अगर (!*p) अणु
		अगर (!entry) /* tree empty */
			जाओ करो_whole;

		/*
		 * If the last node is beक्रमe, advance one to find the next.
		 */
		n = parent;
		अगर (entry->end < start) अणु
			n = rb_next(n);
			अगर (!n)
				जाओ करो_whole;
		पूर्ण
		next = rb_entry(n, काष्ठा block_range, node);

		अगर (next->start <= end) अणु /* add head: [start...][n->start...] */
			काष्ठा block_range *head = दो_स्मृति(माप(काष्ठा block_range));
			अगर (!head)
				वापस iter;

			*head = (काष्ठा block_range)अणु
				.start		= start,
				.end		= next->start - 1,
				.is_target	= 1,
				.is_branch	= 0,
			पूर्ण;

			rb_link_left_of_node(&head->node, &next->node);
			rb_insert_color(&head->node, &block_ranges.root);
			block_range__debug();

			iter.start = head;
			जाओ करो_tail;
		पूर्ण

करो_whole:
		/*
		 * The whole [start..end] range is non-overlapping.
		 */
		entry = दो_स्मृति(माप(काष्ठा block_range));
		अगर (!entry)
			वापस iter;

		*entry = (काष्ठा block_range)अणु
			.start		= start,
			.end		= end,
			.is_target	= 1,
			.is_branch	= 1,
		पूर्ण;

		rb_link_node(&entry->node, parent, p);
		rb_insert_color(&entry->node, &block_ranges.root);
		block_range__debug();

		iter.start = entry;
		iter.end   = entry;
		जाओ करोne;
	पूर्ण

	/*
	 * We found a range that overlapped with ours, split अगर needed.
	 */
	अगर (entry->start < start) अणु /* split: [e->start...][start...] */
		काष्ठा block_range *head = दो_स्मृति(माप(काष्ठा block_range));
		अगर (!head)
			वापस iter;

		*head = (काष्ठा block_range)अणु
			.start		= entry->start,
			.end		= start - 1,
			.is_target	= entry->is_target,
			.is_branch	= 0,

			.coverage	= entry->coverage,
			.entry		= entry->entry,
		पूर्ण;

		entry->start		= start;
		entry->is_target	= 1;
		entry->entry		= 0;

		rb_link_left_of_node(&head->node, &entry->node);
		rb_insert_color(&head->node, &block_ranges.root);
		block_range__debug();

	पूर्ण अन्यथा अगर (entry->start == start)
		entry->is_target = 1;

	iter.start = entry;

करो_tail:
	/*
	 * At this poपूर्णांक we've got: @iter.start = [@start...] but @end can still be
	 * inside or beyond it.
	 */
	entry = iter.start;
	क्रम (;;) अणु
		/*
		 * If @end is inside @entry, split.
		 */
		अगर (end < entry->end) अणु /* split: [...end][...e->end] */
			काष्ठा block_range *tail = दो_स्मृति(माप(काष्ठा block_range));
			अगर (!tail)
				वापस iter;

			*tail = (काष्ठा block_range)अणु
				.start		= end + 1,
				.end		= entry->end,
				.is_target	= 0,
				.is_branch	= entry->is_branch,

				.coverage	= entry->coverage,
				.taken		= entry->taken,
				.pred		= entry->pred,
			पूर्ण;

			entry->end		= end;
			entry->is_branch	= 1;
			entry->taken		= 0;
			entry->pred		= 0;

			rb_link_right_of_node(&tail->node, &entry->node);
			rb_insert_color(&tail->node, &block_ranges.root);
			block_range__debug();

			iter.end = entry;
			जाओ करोne;
		पूर्ण

		/*
		 * If @end matches @entry, करोne
		 */
		अगर (end == entry->end) अणु
			entry->is_branch = 1;
			iter.end = entry;
			जाओ करोne;
		पूर्ण

		next = block_range__next(entry);
		अगर (!next)
			जाओ add_tail;

		/*
		 * If @end is in beyond @entry but not inside @next, add tail.
		 */
		अगर (end < next->start) अणु /* add tail: [...e->end][...end] */
			काष्ठा block_range *tail;
add_tail:
			tail = दो_स्मृति(माप(काष्ठा block_range));
			अगर (!tail)
				वापस iter;

			*tail = (काष्ठा block_range)अणु
				.start		= entry->end + 1,
				.end		= end,
				.is_target	= 0,
				.is_branch	= 1,
			पूर्ण;

			rb_link_right_of_node(&tail->node, &entry->node);
			rb_insert_color(&tail->node, &block_ranges.root);
			block_range__debug();

			iter.end = tail;
			जाओ करोne;
		पूर्ण

		/*
		 * If there is a hole between @entry and @next, fill it.
		 */
		अगर (entry->end + 1 != next->start) अणु
			काष्ठा block_range *hole = दो_स्मृति(माप(काष्ठा block_range));
			अगर (!hole)
				वापस iter;

			*hole = (काष्ठा block_range)अणु
				.start		= entry->end + 1,
				.end		= next->start - 1,
				.is_target	= 0,
				.is_branch	= 0,
			पूर्ण;

			rb_link_left_of_node(&hole->node, &next->node);
			rb_insert_color(&hole->node, &block_ranges.root);
			block_range__debug();
		पूर्ण

		entry = next;
	पूर्ण

करोne:
	निश्चित(iter.start->start == start && iter.start->is_target);
	निश्चित(iter.end->end == end && iter.end->is_branch);

	block_ranges.blocks++;

	वापस iter;
पूर्ण


/*
 * Compute coverage as:
 *
 *    br->coverage / br->sym->max_coverage
 *
 * This ensures each symbol has a 100% spot, to reflect that each symbol has a
 * most covered section.
 *
 * Returns [0-1] क्रम coverage and -1 अगर we had no data what so ever or the
 * symbol करोes not exist.
 */
द्विगुन block_range__coverage(काष्ठा block_range *br)
अणु
	काष्ठा symbol *sym;

	अगर (!br) अणु
		अगर (block_ranges.blocks)
			वापस 0;

		वापस -1;
	पूर्ण

	sym = br->sym;
	अगर (!sym)
		वापस -1;

	वापस (द्विगुन)br->coverage / symbol__annotation(sym)->max_coverage;
पूर्ण
