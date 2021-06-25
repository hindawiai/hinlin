<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/माला.स>

#समावेश "../../util/callchain.h"
#समावेश "../../util/debug.h"
#समावेश "../../util/event.h"
#समावेश "../../util/hist.h"
#समावेश "../../util/map.h"
#समावेश "../../util/maps.h"
#समावेश "../../util/symbol.h"
#समावेश "../../util/sort.h"
#समावेश "../../util/evsel.h"
#समावेश "../../util/srcline.h"
#समावेश "../../util/string2.h"
#समावेश "../../util/thread.h"
#समावेश "../../util/block-info.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

अटल माप_प्रकार callchain__ख_लिखो_left_margin(खाता *fp, पूर्णांक left_margin)
अणु
	पूर्णांक i;
	पूर्णांक ret = ख_लिखो(fp, "            ");

	क्रम (i = 0; i < left_margin; i++)
		ret += ख_लिखो(fp, " ");

	वापस ret;
पूर्ण

अटल माप_प्रकार ipchain__ख_लिखो_graph_line(खाता *fp, पूर्णांक depth, पूर्णांक depth_mask,
					  पूर्णांक left_margin)
अणु
	पूर्णांक i;
	माप_प्रकार ret = callchain__ख_लिखो_left_margin(fp, left_margin);

	क्रम (i = 0; i < depth; i++)
		अगर (depth_mask & (1 << i))
			ret += ख_लिखो(fp, "|          ");
		अन्यथा
			ret += ख_लिखो(fp, "           ");

	ret += ख_लिखो(fp, "\n");

	वापस ret;
पूर्ण

अटल माप_प्रकार ipchain__ख_लिखो_graph(खाता *fp, काष्ठा callchain_node *node,
				     काष्ठा callchain_list *chain,
				     पूर्णांक depth, पूर्णांक depth_mask, पूर्णांक period,
				     u64 total_samples, पूर्णांक left_margin)
अणु
	पूर्णांक i;
	माप_प्रकार ret = 0;
	अक्षर bf[1024], *alloc_str = शून्य;
	अक्षर buf[64];
	स्थिर अक्षर *str;

	ret += callchain__ख_लिखो_left_margin(fp, left_margin);
	क्रम (i = 0; i < depth; i++) अणु
		अगर (depth_mask & (1 << i))
			ret += ख_लिखो(fp, "|");
		अन्यथा
			ret += ख_लिखो(fp, " ");
		अगर (!period && i == depth - 1) अणु
			ret += ख_लिखो(fp, "--");
			ret += callchain_node__ख_लिखो_value(node, fp, total_samples);
			ret += ख_लिखो(fp, "--");
		पूर्ण अन्यथा
			ret += ख_लिखो(fp, "%s", "          ");
	पूर्ण

	str = callchain_list__sym_name(chain, bf, माप(bf), false);

	अगर (symbol_conf.show_branchflag_count) अणु
		callchain_list_counts__म_लिखो_value(chain, शून्य,
						    buf, माप(buf));

		अगर (aप्र_लिखो(&alloc_str, "%s%s", str, buf) < 0)
			str = "Not enough memory!";
		अन्यथा
			str = alloc_str;
	पूर्ण

	ख_माला_दो(str, fp);
	ख_अक्षर_दो('\n', fp);
	मुक्त(alloc_str);

	वापस ret;
पूर्ण

अटल काष्ठा symbol *rem_sq_bracket;
अटल काष्ठा callchain_list rem_hits;

अटल व्योम init_rem_hits(व्योम)
अणु
	rem_sq_bracket = दो_स्मृति(माप(*rem_sq_bracket) + 6);
	अगर (!rem_sq_bracket) अणु
		ख_लिखो(मानक_त्रुटि, "Not enough memory to display remaining hits\n");
		वापस;
	पूर्ण

	म_नकल(rem_sq_bracket->name, "[...]");
	rem_hits.ms.sym = rem_sq_bracket;
पूर्ण

अटल माप_प्रकार __callchain__ख_लिखो_graph(खाता *fp, काष्ठा rb_root *root,
					 u64 total_samples, पूर्णांक depth,
					 पूर्णांक depth_mask, पूर्णांक left_margin)
अणु
	काष्ठा rb_node *node, *next;
	काष्ठा callchain_node *child = शून्य;
	काष्ठा callchain_list *chain;
	पूर्णांक new_depth_mask = depth_mask;
	u64 reमुख्यing;
	माप_प्रकार ret = 0;
	पूर्णांक i;
	uपूर्णांक entries_prपूर्णांकed = 0;
	पूर्णांक cumul_count = 0;

	reमुख्यing = total_samples;

	node = rb_first(root);
	जबतक (node) अणु
		u64 new_total;
		u64 cumul;

		child = rb_entry(node, काष्ठा callchain_node, rb_node);
		cumul = callchain_cumul_hits(child);
		reमुख्यing -= cumul;
		cumul_count += callchain_cumul_counts(child);

		/*
		 * The depth mask manages the output of pipes that show
		 * the depth. We करोn't want to keep the pipes of the current
		 * level क्रम the last child of this depth.
		 * Except अगर we have reमुख्यing filtered hits. They will
		 * supersede the last child
		 */
		next = rb_next(node);
		अगर (!next && (callchain_param.mode != CHAIN_GRAPH_REL || !reमुख्यing))
			new_depth_mask &= ~(1 << (depth - 1));

		/*
		 * But we keep the older depth mask क्रम the line separator
		 * to keep the level link until we reach the last child
		 */
		ret += ipchain__ख_लिखो_graph_line(fp, depth, depth_mask,
						   left_margin);
		i = 0;
		list_क्रम_each_entry(chain, &child->val, list) अणु
			ret += ipchain__ख_लिखो_graph(fp, child, chain, depth,
						      new_depth_mask, i++,
						      total_samples,
						      left_margin);
		पूर्ण

		अगर (callchain_param.mode == CHAIN_GRAPH_REL)
			new_total = child->children_hit;
		अन्यथा
			new_total = total_samples;

		ret += __callchain__ख_लिखो_graph(fp, &child->rb_root, new_total,
						  depth + 1,
						  new_depth_mask | (1 << depth),
						  left_margin);
		node = next;
		अगर (++entries_prपूर्णांकed == callchain_param.prपूर्णांक_limit)
			अवरोध;
	पूर्ण

	अगर (callchain_param.mode == CHAIN_GRAPH_REL &&
		reमुख्यing && reमुख्यing != total_samples) अणु
		काष्ठा callchain_node rem_node = अणु
			.hit = reमुख्यing,
		पूर्ण;

		अगर (!rem_sq_bracket)
			वापस ret;

		अगर (callchain_param.value == CCVAL_COUNT && child && child->parent) अणु
			rem_node.count = child->parent->children_count - cumul_count;
			अगर (rem_node.count <= 0)
				वापस ret;
		पूर्ण

		new_depth_mask &= ~(1 << (depth - 1));
		ret += ipchain__ख_लिखो_graph(fp, &rem_node, &rem_hits, depth,
					      new_depth_mask, 0, total_samples,
					      left_margin);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * If have one single callchain root, करोn't bother prपूर्णांकing
 * its percentage (100 % in fractal mode and the same percentage
 * than the hist in graph mode). This also aव्योम one level of column.
 *
 * However when percent-limit applied, it's possible that single callchain
 * node have dअगरferent (non-100% in fractal mode) percentage.
 */
अटल bool need_percent_display(काष्ठा rb_node *node, u64 parent_samples)
अणु
	काष्ठा callchain_node *cnode;

	अगर (rb_next(node))
		वापस true;

	cnode = rb_entry(node, काष्ठा callchain_node, rb_node);
	वापस callchain_cumul_hits(cnode) != parent_samples;
पूर्ण

अटल माप_प्रकार callchain__ख_लिखो_graph(खाता *fp, काष्ठा rb_root *root,
				       u64 total_samples, u64 parent_samples,
				       पूर्णांक left_margin)
अणु
	काष्ठा callchain_node *cnode;
	काष्ठा callchain_list *chain;
	u32 entries_prपूर्णांकed = 0;
	bool prपूर्णांकed = false;
	काष्ठा rb_node *node;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	अक्षर bf[1024];

	node = rb_first(root);
	अगर (node && !need_percent_display(node, parent_samples)) अणु
		cnode = rb_entry(node, काष्ठा callchain_node, rb_node);
		list_क्रम_each_entry(chain, &cnode->val, list) अणु
			/*
			 * If we sort by symbol, the first entry is the same than
			 * the symbol. No need to prपूर्णांक it otherwise it appears as
			 * displayed twice.
			 */
			अगर (!i++ && field_order == शून्य &&
			    sort_order && strstarts(sort_order, "sym"))
				जारी;

			अगर (!prपूर्णांकed) अणु
				ret += callchain__ख_लिखो_left_margin(fp, left_margin);
				ret += ख_लिखो(fp, "|\n");
				ret += callchain__ख_लिखो_left_margin(fp, left_margin);
				ret += ख_लिखो(fp, "---");
				left_margin += 3;
				prपूर्णांकed = true;
			पूर्ण अन्यथा
				ret += callchain__ख_लिखो_left_margin(fp, left_margin);

			ret += ख_लिखो(fp, "%s",
				       callchain_list__sym_name(chain, bf,
								माप(bf),
								false));

			अगर (symbol_conf.show_branchflag_count)
				ret += callchain_list_counts__म_लिखो_value(
						chain, fp, शून्य, 0);
			ret += ख_लिखो(fp, "\n");

			अगर (++entries_prपूर्णांकed == callchain_param.prपूर्णांक_limit)
				अवरोध;
		पूर्ण
		root = &cnode->rb_root;
	पूर्ण

	अगर (callchain_param.mode == CHAIN_GRAPH_REL)
		total_samples = parent_samples;

	ret += __callchain__ख_लिखो_graph(fp, root, total_samples,
					  1, 1, left_margin);
	अगर (ret) अणु
		/* करो not add a blank line अगर it prपूर्णांकed nothing */
		ret += ख_लिखो(fp, "\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार __callchain__ख_लिखो_flat(खाता *fp, काष्ठा callchain_node *node,
					u64 total_samples)
अणु
	काष्ठा callchain_list *chain;
	माप_प्रकार ret = 0;
	अक्षर bf[1024];

	अगर (!node)
		वापस 0;

	ret += __callchain__ख_लिखो_flat(fp, node->parent, total_samples);


	list_क्रम_each_entry(chain, &node->val, list) अणु
		अगर (chain->ip >= PERF_CONTEXT_MAX)
			जारी;
		ret += ख_लिखो(fp, "                %s\n", callchain_list__sym_name(chain,
					bf, माप(bf), false));
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार callchain__ख_लिखो_flat(खाता *fp, काष्ठा rb_root *tree,
				      u64 total_samples)
अणु
	माप_प्रकार ret = 0;
	u32 entries_prपूर्णांकed = 0;
	काष्ठा callchain_node *chain;
	काष्ठा rb_node *rb_node = rb_first(tree);

	जबतक (rb_node) अणु
		chain = rb_entry(rb_node, काष्ठा callchain_node, rb_node);

		ret += ख_लिखो(fp, "           ");
		ret += callchain_node__ख_लिखो_value(chain, fp, total_samples);
		ret += ख_लिखो(fp, "\n");
		ret += __callchain__ख_लिखो_flat(fp, chain, total_samples);
		ret += ख_लिखो(fp, "\n");
		अगर (++entries_prपूर्णांकed == callchain_param.prपूर्णांक_limit)
			अवरोध;

		rb_node = rb_next(rb_node);
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार __callchain__ख_लिखो_folded(खाता *fp, काष्ठा callchain_node *node)
अणु
	स्थिर अक्षर *sep = symbol_conf.field_sep ?: ";";
	काष्ठा callchain_list *chain;
	माप_प्रकार ret = 0;
	अक्षर bf[1024];
	bool first;

	अगर (!node)
		वापस 0;

	ret += __callchain__ख_लिखो_folded(fp, node->parent);

	first = (ret == 0);
	list_क्रम_each_entry(chain, &node->val, list) अणु
		अगर (chain->ip >= PERF_CONTEXT_MAX)
			जारी;
		ret += ख_लिखो(fp, "%s%s", first ? "" : sep,
			       callchain_list__sym_name(chain,
						bf, माप(bf), false));
		first = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार callchain__ख_लिखो_folded(खाता *fp, काष्ठा rb_root *tree,
					u64 total_samples)
अणु
	माप_प्रकार ret = 0;
	u32 entries_prपूर्णांकed = 0;
	काष्ठा callchain_node *chain;
	काष्ठा rb_node *rb_node = rb_first(tree);

	जबतक (rb_node) अणु

		chain = rb_entry(rb_node, काष्ठा callchain_node, rb_node);

		ret += callchain_node__ख_लिखो_value(chain, fp, total_samples);
		ret += ख_लिखो(fp, " ");
		ret += __callchain__ख_लिखो_folded(fp, chain);
		ret += ख_लिखो(fp, "\n");
		अगर (++entries_prपूर्णांकed == callchain_param.prपूर्णांक_limit)
			अवरोध;

		rb_node = rb_next(rb_node);
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार hist_entry_callchain__ख_लिखो(काष्ठा hist_entry *he,
					    u64 total_samples, पूर्णांक left_margin,
					    खाता *fp)
अणु
	u64 parent_samples = he->stat.period;

	अगर (symbol_conf.cumulate_callchain)
		parent_samples = he->stat_acc->period;

	चयन (callchain_param.mode) अणु
	हाल CHAIN_GRAPH_REL:
		वापस callchain__ख_लिखो_graph(fp, &he->sorted_chain, total_samples,
						parent_samples, left_margin);
		अवरोध;
	हाल CHAIN_GRAPH_ABS:
		वापस callchain__ख_लिखो_graph(fp, &he->sorted_chain, total_samples,
						parent_samples, left_margin);
		अवरोध;
	हाल CHAIN_FLAT:
		वापस callchain__ख_लिखो_flat(fp, &he->sorted_chain, total_samples);
		अवरोध;
	हाल CHAIN_FOLDED:
		वापस callchain__ख_लिखो_folded(fp, &he->sorted_chain, total_samples);
		अवरोध;
	हाल CHAIN_NONE:
		अवरोध;
	शेष:
		pr_err("Bad callchain mode\n");
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __hist_entry__snम_लिखो(काष्ठा hist_entry *he, काष्ठा perf_hpp *hpp,
			   काष्ठा perf_hpp_list *hpp_list)
अणु
	स्थिर अक्षर *sep = symbol_conf.field_sep;
	काष्ठा perf_hpp_fmt *fmt;
	अक्षर *start = hpp->buf;
	पूर्णांक ret;
	bool first = true;

	अगर (symbol_conf.exclude_other && !he->parent)
		वापस 0;

	perf_hpp_list__क्रम_each_क्रमmat(hpp_list, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, he->hists))
			जारी;

		/*
		 * If there's no field_sep, we still need
		 * to display initial '  '.
		 */
		अगर (!sep || !first) अणु
			ret = scnम_लिखो(hpp->buf, hpp->size, "%s", sep ?: "  ");
			advance_hpp(hpp, ret);
		पूर्ण अन्यथा
			first = false;

		अगर (perf_hpp__use_color() && fmt->color)
			ret = fmt->color(fmt, hpp, he);
		अन्यथा
			ret = fmt->entry(fmt, hpp, he);

		ret = hist_entry__snम_लिखो_alignment(he, hpp, fmt, ret);
		advance_hpp(hpp, ret);
	पूर्ण

	वापस hpp->buf - start;
पूर्ण

अटल पूर्णांक hist_entry__snम_लिखो(काष्ठा hist_entry *he, काष्ठा perf_hpp *hpp)
अणु
	वापस __hist_entry__snम_लिखो(he, hpp, he->hists->hpp_list);
पूर्ण

अटल पूर्णांक hist_entry__hierarchy_ख_लिखो(काष्ठा hist_entry *he,
					 काष्ठा perf_hpp *hpp,
					 काष्ठा hists *hists,
					 खाता *fp)
अणु
	स्थिर अक्षर *sep = symbol_conf.field_sep;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	अक्षर *buf = hpp->buf;
	माप_प्रकार size = hpp->size;
	पूर्णांक ret, prपूर्णांकed = 0;
	bool first = true;

	अगर (symbol_conf.exclude_other && !he->parent)
		वापस 0;

	ret = scnम_लिखो(hpp->buf, hpp->size, "%*s", he->depth * HIERARCHY_INDENT, "");
	advance_hpp(hpp, ret);

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		/*
		 * If there's no field_sep, we still need
		 * to display initial '  '.
		 */
		अगर (!sep || !first) अणु
			ret = scnम_लिखो(hpp->buf, hpp->size, "%s", sep ?: "  ");
			advance_hpp(hpp, ret);
		पूर्ण अन्यथा
			first = false;

		अगर (perf_hpp__use_color() && fmt->color)
			ret = fmt->color(fmt, hpp, he);
		अन्यथा
			ret = fmt->entry(fmt, hpp, he);

		ret = hist_entry__snम_लिखो_alignment(he, hpp, fmt, ret);
		advance_hpp(hpp, ret);
	पूर्ण

	अगर (!sep)
		ret = scnम_लिखो(hpp->buf, hpp->size, "%*s",
				(hists->nr_hpp_node - 2) * HIERARCHY_INDENT, "");
	advance_hpp(hpp, ret);

	prपूर्णांकed += ख_लिखो(fp, "%s", buf);

	perf_hpp_list__क्रम_each_क्रमmat(he->hpp_list, fmt) अणु
		hpp->buf  = buf;
		hpp->size = size;

		/*
		 * No need to call hist_entry__snम_लिखो_alignment() since this
		 * fmt is always the last column in the hierarchy mode.
		 */
		अगर (perf_hpp__use_color() && fmt->color)
			fmt->color(fmt, hpp, he);
		अन्यथा
			fmt->entry(fmt, hpp, he);

		/*
		 * dynamic entries are right-aligned but we want left-aligned
		 * in the hierarchy mode
		 */
		prपूर्णांकed += ख_लिखो(fp, "%s%s", sep ?: "  ", skip_spaces(buf));
	पूर्ण
	prपूर्णांकed += अ_दो('\n', fp);

	अगर (he->leaf && hist_entry__has_callchains(he) && symbol_conf.use_callchain) अणु
		u64 total = hists__total_period(hists);

		prपूर्णांकed += hist_entry_callchain__ख_लिखो(he, total, 0, fp);
		जाओ out;
	पूर्ण

out:
	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_entry__block_ख_लिखो(काष्ठा hist_entry *he,
				     अक्षर *bf, माप_प्रकार size,
				     खाता *fp)
अणु
	काष्ठा block_hist *bh = container_of(he, काष्ठा block_hist, he);
	पूर्णांक ret = 0;

	क्रम (अचिन्हित पूर्णांक i = 0; i < bh->block_hists.nr_entries; i++) अणु
		काष्ठा perf_hpp hpp = अणु
			.buf		= bf,
			.size		= size,
			.skip		= false,
		पूर्ण;

		bh->block_idx = i;
		hist_entry__snम_लिखो(he, &hpp);

		अगर (!hpp.skip)
			ret += ख_लिखो(fp, "%s\n", bf);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hist_entry__inभागidual_block_ख_लिखो(काष्ठा hist_entry *he,
						अक्षर *bf, माप_प्रकार size,
						खाता *fp)
अणु
	पूर्णांक ret = 0;

	काष्ठा perf_hpp hpp = अणु
		.buf		= bf,
		.size		= size,
		.skip		= false,
	पूर्ण;

	hist_entry__snम_लिखो(he, &hpp);
	अगर (!hpp.skip)
		ret += ख_लिखो(fp, "%s\n", bf);

	वापस ret;
पूर्ण

अटल पूर्णांक hist_entry__ख_लिखो(काष्ठा hist_entry *he, माप_प्रकार size,
			       अक्षर *bf, माप_प्रकार bfsz, खाता *fp,
			       bool ignore_callchains)
अणु
	पूर्णांक ret;
	पूर्णांक callchain_ret = 0;
	काष्ठा perf_hpp hpp = अणु
		.buf		= bf,
		.size		= size,
	पूर्ण;
	काष्ठा hists *hists = he->hists;
	u64 total_period = hists->stats.total_period;

	अगर (size == 0 || size > bfsz)
		size = hpp.size = bfsz;

	अगर (symbol_conf.report_hierarchy)
		वापस hist_entry__hierarchy_ख_लिखो(he, &hpp, hists, fp);

	अगर (symbol_conf.report_block)
		वापस hist_entry__block_ख_लिखो(he, bf, size, fp);

	अगर (symbol_conf.report_inभागidual_block)
		वापस hist_entry__inभागidual_block_ख_लिखो(he, bf, size, fp);

	hist_entry__snम_लिखो(he, &hpp);

	ret = ख_लिखो(fp, "%s\n", bf);

	अगर (hist_entry__has_callchains(he) && !ignore_callchains)
		callchain_ret = hist_entry_callchain__ख_लिखो(he, total_period,
							      0, fp);

	ret += callchain_ret;

	वापस ret;
पूर्ण

अटल पूर्णांक prपूर्णांक_hierarchy_indent(स्थिर अक्षर *sep, पूर्णांक indent,
				  स्थिर अक्षर *line, खाता *fp)
अणु
	पूर्णांक width;

	अगर (sep != शून्य || indent < 2)
		वापस 0;

	width = (indent - 2) * HIERARCHY_INDENT;

	वापस ख_लिखो(fp, "%-*.*s", width, width, line);
पूर्ण

अटल पूर्णांक hists__ख_लिखो_hierarchy_headers(काष्ठा hists *hists,
					    काष्ठा perf_hpp *hpp, खाता *fp)
अणु
	bool first_node, first_col;
	पूर्णांक indent;
	पूर्णांक depth;
	अचिन्हित width = 0;
	अचिन्हित header_width = 0;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	स्थिर अक्षर *sep = symbol_conf.field_sep;

	indent = hists->nr_hpp_node;

	/* preserve max indent depth क्रम column headers */
	prपूर्णांक_hierarchy_indent(sep, indent, " ", fp);

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);

	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		fmt->header(fmt, hpp, hists, 0, शून्य);
		ख_लिखो(fp, "%s%s", hpp->buf, sep ?: "  ");
	पूर्ण

	/* combine sort headers with ' / ' */
	first_node = true;
	list_क्रम_each_entry_जारी(fmt_node, &hists->hpp_क्रमmats, list) अणु
		अगर (!first_node)
			header_width += ख_लिखो(fp, " / ");
		first_node = false;

		first_col = true;
		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
			अगर (perf_hpp__should_skip(fmt, hists))
				जारी;

			अगर (!first_col)
				header_width += ख_लिखो(fp, "+");
			first_col = false;

			fmt->header(fmt, hpp, hists, 0, शून्य);

			header_width += ख_लिखो(fp, "%s", strim(hpp->buf));
		पूर्ण
	पूर्ण

	ख_लिखो(fp, "\n# ");

	/* preserve max indent depth क्रम initial करोts */
	prपूर्णांक_hierarchy_indent(sep, indent, करोts, fp);

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);

	first_col = true;
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		अगर (!first_col)
			ख_लिखो(fp, "%s", sep ?: "..");
		first_col = false;

		width = fmt->width(fmt, hpp, hists);
		ख_लिखो(fp, "%.*s", width, करोts);
	पूर्ण

	depth = 0;
	list_क्रम_each_entry_जारी(fmt_node, &hists->hpp_क्रमmats, list) अणु
		first_col = true;
		width = depth * HIERARCHY_INDENT;

		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
			अगर (perf_hpp__should_skip(fmt, hists))
				जारी;

			अगर (!first_col)
				width++;  /* क्रम '+' sign between column header */
			first_col = false;

			width += fmt->width(fmt, hpp, hists);
		पूर्ण

		अगर (width > header_width)
			header_width = width;

		depth++;
	पूर्ण

	ख_लिखो(fp, "%s%-.*s", sep ?: "  ", header_width, करोts);

	ख_लिखो(fp, "\n#\n");

	वापस 2;
पूर्ण

अटल व्योम ख_लिखो_line(काष्ठा hists *hists, काष्ठा perf_hpp *hpp,
			 पूर्णांक line, खाता *fp)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	स्थिर अक्षर *sep = symbol_conf.field_sep;
	bool first = true;
	पूर्णांक span = 0;

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, hists))
			जारी;

		अगर (!first && !span)
			ख_लिखो(fp, "%s", sep ?: "  ");
		अन्यथा
			first = false;

		fmt->header(fmt, hpp, hists, line, &span);

		अगर (!span)
			ख_लिखो(fp, "%s", hpp->buf);
	पूर्ण
पूर्ण

अटल पूर्णांक
hists__ख_लिखो_standard_headers(काष्ठा hists *hists,
				काष्ठा perf_hpp *hpp,
				खाता *fp)
अणु
	काष्ठा perf_hpp_list *hpp_list = hists->hpp_list;
	काष्ठा perf_hpp_fmt *fmt;
	अचिन्हित पूर्णांक width;
	स्थिर अक्षर *sep = symbol_conf.field_sep;
	bool first = true;
	पूर्णांक line;

	क्रम (line = 0; line < hpp_list->nr_header_lines; line++) अणु
		/* first # is displayed one level up */
		अगर (line)
			ख_लिखो(fp, "# ");
		ख_लिखो_line(hists, hpp, line, fp);
		ख_लिखो(fp, "\n");
	पूर्ण

	अगर (sep)
		वापस hpp_list->nr_header_lines;

	first = true;

	ख_लिखो(fp, "# ");

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अचिन्हित पूर्णांक i;

		अगर (perf_hpp__should_skip(fmt, hists))
			जारी;

		अगर (!first)
			ख_लिखो(fp, "%s", sep ?: "  ");
		अन्यथा
			first = false;

		width = fmt->width(fmt, hpp, hists);
		क्रम (i = 0; i < width; i++)
			ख_लिखो(fp, ".");
	पूर्ण

	ख_लिखो(fp, "\n");
	ख_लिखो(fp, "#\n");
	वापस hpp_list->nr_header_lines + 2;
पूर्ण

पूर्णांक hists__ख_लिखो_headers(काष्ठा hists *hists, खाता *fp)
अणु
	अक्षर bf[1024];
	काष्ठा perf_hpp dummy_hpp = अणु
		.buf	= bf,
		.size	= माप(bf),
	पूर्ण;

	ख_लिखो(fp, "# ");

	अगर (symbol_conf.report_hierarchy)
		वापस hists__ख_लिखो_hierarchy_headers(hists, &dummy_hpp, fp);
	अन्यथा
		वापस hists__ख_लिखो_standard_headers(hists, &dummy_hpp, fp);

पूर्ण

माप_प्रकार hists__ख_लिखो(काष्ठा hists *hists, bool show_header, पूर्णांक max_rows,
		      पूर्णांक max_cols, भग्न min_pcnt, खाता *fp,
		      bool ignore_callchains)
अणु
	काष्ठा rb_node *nd;
	माप_प्रकार ret = 0;
	स्थिर अक्षर *sep = symbol_conf.field_sep;
	पूर्णांक nr_rows = 0;
	माप_प्रकार linesz;
	अक्षर *line = शून्य;
	अचिन्हित indent;

	init_rem_hits();

	hists__reset_column_width(hists);

	अगर (symbol_conf.col_width_list_str)
		perf_hpp__set_user_width(symbol_conf.col_width_list_str);

	अगर (show_header)
		nr_rows += hists__ख_लिखो_headers(hists, fp);

	अगर (max_rows && nr_rows >= max_rows)
		जाओ out;

	linesz = hists__sort_list_width(hists) + 3 + 1;
	linesz += perf_hpp__color_overhead();
	line = दो_स्मृति(linesz);
	अगर (line == शून्य) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	indent = hists__overhead_width(hists) + 4;

	क्रम (nd = rb_first_cached(&hists->entries); nd;
	     nd = __rb_hierarchy_next(nd, HMD_FORCE_CHILD)) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		भग्न percent;

		अगर (h->filtered)
			जारी;

		अगर (symbol_conf.report_inभागidual_block)
			percent = block_info__total_cycles_percent(h);
		अन्यथा
			percent = hist_entry__get_percent_limit(h);

		अगर (percent < min_pcnt)
			जारी;

		ret += hist_entry__ख_लिखो(h, max_cols, line, linesz, fp, ignore_callchains);

		अगर (max_rows && ++nr_rows >= max_rows)
			अवरोध;

		/*
		 * If all children are filtered out or percent-limited,
		 * display "no entry >= x.xx%" message.
		 */
		अगर (!h->leaf && !hist_entry__has_hierarchy_children(h, min_pcnt)) अणु
			पूर्णांक depth = hists->nr_hpp_node + h->depth + 1;

			prपूर्णांक_hierarchy_indent(sep, depth, " ", fp);
			ख_लिखो(fp, "%*sno entry >= %.2f%%\n", indent, "", min_pcnt);

			अगर (max_rows && ++nr_rows >= max_rows)
				अवरोध;
		पूर्ण

		अगर (h->ms.map == शून्य && verbose > 1) अणु
			maps__ख_लिखो(h->thपढ़ो->maps, fp);
			ख_लिखो(fp, "%.10s end\n", graph_करोtted_line);
		पूर्ण
	पूर्ण

	मुक्त(line);
out:
	zमुक्त(&rem_sq_bracket);

	वापस ret;
पूर्ण

माप_प्रकार events_stats__ख_लिखो(काष्ठा events_stats *stats, खाता *fp,
			     bool skip_empty)
अणु
	पूर्णांक i;
	माप_प्रकार ret = 0;
	u32 total = stats->nr_events[0];

	क्रम (i = 0; i < PERF_RECORD_HEADER_MAX; ++i) अणु
		स्थिर अक्षर *name;

		name = perf_event__name(i);
		अगर (!म_भेद(name, "UNKNOWN"))
			जारी;
		अगर (skip_empty && !stats->nr_events[i])
			जारी;

		अगर (i && total) अणु
			ret += ख_लिखो(fp, "%16s events: %10d  (%4.1f%%)\n",
				       name, stats->nr_events[i],
				       100.0 * stats->nr_events[i] / total);
		पूर्ण अन्यथा अणु
			ret += ख_लिखो(fp, "%16s events: %10d\n",
				       name, stats->nr_events[i]);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
