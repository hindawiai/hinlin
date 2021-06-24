<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interconnect framework core driver
 *
 * Copyright (c) 2017-2019, Linaro Ltd.
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/overflow.h>

#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

अटल DEFINE_IDR(icc_idr);
अटल LIST_HEAD(icc_providers);
अटल पूर्णांक providers_count;
अटल bool synced_state;
अटल DEFINE_MUTEX(icc_lock);
अटल काष्ठा dentry *icc_debugfs_dir;

अटल व्योम icc_summary_show_one(काष्ठा seq_file *s, काष्ठा icc_node *n)
अणु
	अगर (!n)
		वापस;

	seq_म_लिखो(s, "%-42s %12u %12u\n",
		   n->name, n->avg_bw, n->peak_bw);
पूर्ण

अटल पूर्णांक icc_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा icc_provider *provider;

	seq_माला_दो(s, " node                                  tag          avg         peak\n");
	seq_माला_दो(s, "--------------------------------------------------------------------\n");

	mutex_lock(&icc_lock);

	list_क्रम_each_entry(provider, &icc_providers, provider_list) अणु
		काष्ठा icc_node *n;

		list_क्रम_each_entry(n, &provider->nodes, node_list) अणु
			काष्ठा icc_req *r;

			icc_summary_show_one(s, n);
			hlist_क्रम_each_entry(r, &n->req_list, req_node) अणु
				u32 avg_bw = 0, peak_bw = 0;

				अगर (!r->dev)
					जारी;

				अगर (r->enabled) अणु
					avg_bw = r->avg_bw;
					peak_bw = r->peak_bw;
				पूर्ण

				seq_म_लिखो(s, "  %-27s %12u %12u %12u\n",
					   dev_name(r->dev), r->tag, avg_bw, peak_bw);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&icc_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(icc_summary);

अटल व्योम icc_graph_show_link(काष्ठा seq_file *s, पूर्णांक level,
				काष्ठा icc_node *n, काष्ठा icc_node *m)
अणु
	seq_म_लिखो(s, "%s\"%d:%s\" -> \"%d:%s\"\n",
		   level == 2 ? "\t\t" : "\t",
		   n->id, n->name, m->id, m->name);
पूर्ण

अटल व्योम icc_graph_show_node(काष्ठा seq_file *s, काष्ठा icc_node *n)
अणु
	seq_म_लिखो(s, "\t\t\"%d:%s\" [label=\"%d:%s",
		   n->id, n->name, n->id, n->name);
	seq_म_लिखो(s, "\n\t\t\t|avg_bw=%ukBps", n->avg_bw);
	seq_म_लिखो(s, "\n\t\t\t|peak_bw=%ukBps", n->peak_bw);
	seq_माला_दो(s, "\"]\n");
पूर्ण

अटल पूर्णांक icc_graph_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा icc_provider *provider;
	काष्ठा icc_node *n;
	पूर्णांक cluster_index = 0;
	पूर्णांक i;

	seq_माला_दो(s, "digraph {\n\trankdir = LR\n\tnode [shape = record]\n");
	mutex_lock(&icc_lock);

	/* draw providers as cluster subgraphs */
	cluster_index = 0;
	list_क्रम_each_entry(provider, &icc_providers, provider_list) अणु
		seq_म_लिखो(s, "\tsubgraph cluster_%d {\n", ++cluster_index);
		अगर (provider->dev)
			seq_म_लिखो(s, "\t\tlabel = \"%s\"\n",
				   dev_name(provider->dev));

		/* draw nodes */
		list_क्रम_each_entry(n, &provider->nodes, node_list)
			icc_graph_show_node(s, n);

		/* draw पूर्णांकernal links */
		list_क्रम_each_entry(n, &provider->nodes, node_list)
			क्रम (i = 0; i < n->num_links; ++i)
				अगर (n->provider == n->links[i]->provider)
					icc_graph_show_link(s, 2, n,
							    n->links[i]);

		seq_माला_दो(s, "\t}\n");
	पूर्ण

	/* draw बाह्यal links */
	list_क्रम_each_entry(provider, &icc_providers, provider_list)
		list_क्रम_each_entry(n, &provider->nodes, node_list)
			क्रम (i = 0; i < n->num_links; ++i)
				अगर (n->provider != n->links[i]->provider)
					icc_graph_show_link(s, 1, n,
							    n->links[i]);

	mutex_unlock(&icc_lock);
	seq_माला_दो(s, "}");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(icc_graph);

अटल काष्ठा icc_node *node_find(स्थिर पूर्णांक id)
अणु
	वापस idr_find(&icc_idr, id);
पूर्ण

अटल काष्ठा icc_path *path_init(काष्ठा device *dev, काष्ठा icc_node *dst,
				  sमाप_प्रकार num_nodes)
अणु
	काष्ठा icc_node *node = dst;
	काष्ठा icc_path *path;
	पूर्णांक i;

	path = kzalloc(काष्ठा_size(path, reqs, num_nodes), GFP_KERNEL);
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);

	path->num_nodes = num_nodes;

	क्रम (i = num_nodes - 1; i >= 0; i--) अणु
		node->provider->users++;
		hlist_add_head(&path->reqs[i].req_node, &node->req_list);
		path->reqs[i].node = node;
		path->reqs[i].dev = dev;
		path->reqs[i].enabled = true;
		/* reference to previous node was saved during path traversal */
		node = node->reverse;
	पूर्ण

	वापस path;
पूर्ण

अटल काष्ठा icc_path *path_find(काष्ठा device *dev, काष्ठा icc_node *src,
				  काष्ठा icc_node *dst)
अणु
	काष्ठा icc_path *path = ERR_PTR(-EPROBE_DEFER);
	काष्ठा icc_node *n, *node = शून्य;
	काष्ठा list_head traverse_list;
	काष्ठा list_head edge_list;
	काष्ठा list_head visited_list;
	माप_प्रकार i, depth = 1;
	bool found = false;

	INIT_LIST_HEAD(&traverse_list);
	INIT_LIST_HEAD(&edge_list);
	INIT_LIST_HEAD(&visited_list);

	list_add(&src->search_list, &traverse_list);
	src->reverse = शून्य;

	करो अणु
		list_क्रम_each_entry_safe(node, n, &traverse_list, search_list) अणु
			अगर (node == dst) अणु
				found = true;
				list_splice_init(&edge_list, &visited_list);
				list_splice_init(&traverse_list, &visited_list);
				अवरोध;
			पूर्ण
			क्रम (i = 0; i < node->num_links; i++) अणु
				काष्ठा icc_node *पंचांगp = node->links[i];

				अगर (!पंचांगp) अणु
					path = ERR_PTR(-ENOENT);
					जाओ out;
				पूर्ण

				अगर (पंचांगp->is_traversed)
					जारी;

				पंचांगp->is_traversed = true;
				पंचांगp->reverse = node;
				list_add_tail(&पंचांगp->search_list, &edge_list);
			पूर्ण
		पूर्ण

		अगर (found)
			अवरोध;

		list_splice_init(&traverse_list, &visited_list);
		list_splice_init(&edge_list, &traverse_list);

		/* count the hops including the source */
		depth++;

	पूर्ण जबतक (!list_empty(&traverse_list));

out:

	/* reset the traversed state */
	list_क्रम_each_entry_reverse(n, &visited_list, search_list)
		n->is_traversed = false;

	अगर (found)
		path = path_init(dev, dst, depth);

	वापस path;
पूर्ण

/*
 * We want the path to honor all bandwidth requests, so the average and peak
 * bandwidth requirements from each consumer are aggregated at each node.
 * The aggregation is platक्रमm specअगरic, so each platक्रमm can customize it by
 * implementing its own aggregate() function.
 */

अटल पूर्णांक aggregate_requests(काष्ठा icc_node *node)
अणु
	काष्ठा icc_provider *p = node->provider;
	काष्ठा icc_req *r;
	u32 avg_bw, peak_bw;

	node->avg_bw = 0;
	node->peak_bw = 0;

	अगर (p->pre_aggregate)
		p->pre_aggregate(node);

	hlist_क्रम_each_entry(r, &node->req_list, req_node) अणु
		अगर (r->enabled) अणु
			avg_bw = r->avg_bw;
			peak_bw = r->peak_bw;
		पूर्ण अन्यथा अणु
			avg_bw = 0;
			peak_bw = 0;
		पूर्ण
		p->aggregate(node, r->tag, avg_bw, peak_bw,
			     &node->avg_bw, &node->peak_bw);

		/* during boot use the initial bandwidth as a न्यूनमान value */
		अगर (!synced_state) अणु
			node->avg_bw = max(node->avg_bw, node->init_avg);
			node->peak_bw = max(node->peak_bw, node->init_peak);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apply_स्थिरraपूर्णांकs(काष्ठा icc_path *path)
अणु
	काष्ठा icc_node *next, *prev = शून्य;
	काष्ठा icc_provider *p;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < path->num_nodes; i++) अणु
		next = path->reqs[i].node;
		p = next->provider;

		/* both endpoपूर्णांकs should be valid master-slave pairs */
		अगर (!prev || (p != prev->provider && !p->पूर्णांकer_set)) अणु
			prev = next;
			जारी;
		पूर्ण

		/* set the स्थिरraपूर्णांकs */
		ret = p->set(prev, next);
		अगर (ret)
			जाओ out;

		prev = next;
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक icc_std_aggregate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
		      u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
अणु
	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(icc_std_aggregate);

/* of_icc_xlate_onecell() - Translate function using a single index.
 * @spec: OF phandle args to map पूर्णांकo an पूर्णांकerconnect node.
 * @data: निजी data (poपूर्णांकer to काष्ठा icc_onecell_data)
 *
 * This is a generic translate function that can be used to model simple
 * पूर्णांकerconnect providers that have one device tree node and provide
 * multiple पूर्णांकerconnect nodes. A single cell is used as an index पूर्णांकo
 * an array of icc nodes specअगरied in the icc_onecell_data काष्ठा when
 * रेजिस्टरing the provider.
 */
काष्ठा icc_node *of_icc_xlate_onecell(काष्ठा of_phandle_args *spec,
				      व्योम *data)
अणु
	काष्ठा icc_onecell_data *icc_data = data;
	अचिन्हित पूर्णांक idx = spec->args[0];

	अगर (idx >= icc_data->num_nodes) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस icc_data->nodes[idx];
पूर्ण
EXPORT_SYMBOL_GPL(of_icc_xlate_onecell);

/**
 * of_icc_get_from_provider() - Look-up पूर्णांकerconnect node
 * @spec: OF phandle args to use क्रम look-up
 *
 * Looks क्रम पूर्णांकerconnect provider under the node specअगरied by @spec and अगर
 * found, uses xlate function of the provider to map phandle args to node.
 *
 * Returns a valid poपूर्णांकer to काष्ठा icc_node_data on success or ERR_PTR()
 * on failure.
 */
काष्ठा icc_node_data *of_icc_get_from_provider(काष्ठा of_phandle_args *spec)
अणु
	काष्ठा icc_node *node = ERR_PTR(-EPROBE_DEFER);
	काष्ठा icc_node_data *data = शून्य;
	काष्ठा icc_provider *provider;

	अगर (!spec)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&icc_lock);
	list_क्रम_each_entry(provider, &icc_providers, provider_list) अणु
		अगर (provider->dev->of_node == spec->np) अणु
			अगर (provider->xlate_extended) अणु
				data = provider->xlate_extended(spec, provider->data);
				अगर (!IS_ERR(data)) अणु
					node = data->node;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				node = provider->xlate(spec, provider->data);
				अगर (!IS_ERR(node))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&icc_lock);

	अगर (IS_ERR(node))
		वापस ERR_CAST(node);

	अगर (!data) अणु
		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			वापस ERR_PTR(-ENOMEM);
		data->node = node;
	पूर्ण

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(of_icc_get_from_provider);

अटल व्योम devm_icc_release(काष्ठा device *dev, व्योम *res)
अणु
	icc_put(*(काष्ठा icc_path **)res);
पूर्ण

काष्ठा icc_path *devm_of_icc_get(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा icc_path **ptr, *path;

	ptr = devres_alloc(devm_icc_release, माप(**ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	path = of_icc_get(dev, name);
	अगर (!IS_ERR(path)) अणु
		*ptr = path;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस path;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_icc_get);

/**
 * of_icc_get_by_index() - get a path handle from a DT node based on index
 * @dev: device poपूर्णांकer क्रम the consumer device
 * @idx: पूर्णांकerconnect path index
 *
 * This function will search क्रम a path between two endpoपूर्णांकs and वापस an
 * icc_path handle on success. Use icc_put() to release स्थिरraपूर्णांकs when they
 * are not needed anymore.
 * If the पूर्णांकerconnect API is disabled, शून्य is वापसed and the consumer
 * drivers will still build. Drivers are मुक्त to handle this specअगरically,
 * but they करोn't have to.
 *
 * Return: icc_path poपूर्णांकer on success or ERR_PTR() on error. शून्य is वापसed
 * when the API is disabled or the "interconnects" DT property is missing.
 */
काष्ठा icc_path *of_icc_get_by_index(काष्ठा device *dev, पूर्णांक idx)
अणु
	काष्ठा icc_path *path;
	काष्ठा icc_node_data *src_data, *dst_data;
	काष्ठा device_node *np;
	काष्ठा of_phandle_args src_args, dst_args;
	पूर्णांक ret;

	अगर (!dev || !dev->of_node)
		वापस ERR_PTR(-ENODEV);

	np = dev->of_node;

	/*
	 * When the consumer DT node करो not have "interconnects" property
	 * वापस a शून्य path to skip setting स्थिरraपूर्णांकs.
	 */
	अगर (!of_find_property(np, "interconnects", शून्य))
		वापस शून्य;

	/*
	 * We use a combination of phandle and specअगरier क्रम endpoपूर्णांक. For now
	 * lets support only global ids and extend this in the future अगर needed
	 * without अवरोधing DT compatibility.
	 */
	ret = of_parse_phandle_with_args(np, "interconnects",
					 "#interconnect-cells", idx * 2,
					 &src_args);
	अगर (ret)
		वापस ERR_PTR(ret);

	of_node_put(src_args.np);

	ret = of_parse_phandle_with_args(np, "interconnects",
					 "#interconnect-cells", idx * 2 + 1,
					 &dst_args);
	अगर (ret)
		वापस ERR_PTR(ret);

	of_node_put(dst_args.np);

	src_data = of_icc_get_from_provider(&src_args);

	अगर (IS_ERR(src_data)) अणु
		dev_err_probe(dev, PTR_ERR(src_data), "error finding src node\n");
		वापस ERR_CAST(src_data);
	पूर्ण

	dst_data = of_icc_get_from_provider(&dst_args);

	अगर (IS_ERR(dst_data)) अणु
		dev_err_probe(dev, PTR_ERR(dst_data), "error finding dst node\n");
		kमुक्त(src_data);
		वापस ERR_CAST(dst_data);
	पूर्ण

	mutex_lock(&icc_lock);
	path = path_find(dev, src_data->node, dst_data->node);
	mutex_unlock(&icc_lock);
	अगर (IS_ERR(path)) अणु
		dev_err(dev, "%s: invalid path=%ld\n", __func__, PTR_ERR(path));
		जाओ मुक्त_icc_data;
	पूर्ण

	अगर (src_data->tag && src_data->tag == dst_data->tag)
		icc_set_tag(path, src_data->tag);

	path->name = kaप्र_लिखो(GFP_KERNEL, "%s-%s",
			       src_data->node->name, dst_data->node->name);
	अगर (!path->name) अणु
		kमुक्त(path);
		path = ERR_PTR(-ENOMEM);
	पूर्ण

मुक्त_icc_data:
	kमुक्त(src_data);
	kमुक्त(dst_data);
	वापस path;
पूर्ण
EXPORT_SYMBOL_GPL(of_icc_get_by_index);

/**
 * of_icc_get() - get a path handle from a DT node based on name
 * @dev: device poपूर्णांकer क्रम the consumer device
 * @name: पूर्णांकerconnect path name
 *
 * This function will search क्रम a path between two endpoपूर्णांकs and वापस an
 * icc_path handle on success. Use icc_put() to release स्थिरraपूर्णांकs when they
 * are not needed anymore.
 * If the पूर्णांकerconnect API is disabled, शून्य is वापसed and the consumer
 * drivers will still build. Drivers are मुक्त to handle this specअगरically,
 * but they करोn't have to.
 *
 * Return: icc_path poपूर्णांकer on success or ERR_PTR() on error. शून्य is वापसed
 * when the API is disabled or the "interconnects" DT property is missing.
 */
काष्ठा icc_path *of_icc_get(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np;
	पूर्णांक idx = 0;

	अगर (!dev || !dev->of_node)
		वापस ERR_PTR(-ENODEV);

	np = dev->of_node;

	/*
	 * When the consumer DT node करो not have "interconnects" property
	 * वापस a शून्य path to skip setting स्थिरraपूर्णांकs.
	 */
	अगर (!of_find_property(np, "interconnects", शून्य))
		वापस शून्य;

	/*
	 * We use a combination of phandle and specअगरier क्रम endpoपूर्णांक. For now
	 * lets support only global ids and extend this in the future अगर needed
	 * without अवरोधing DT compatibility.
	 */
	अगर (name) अणु
		idx = of_property_match_string(np, "interconnect-names", name);
		अगर (idx < 0)
			वापस ERR_PTR(idx);
	पूर्ण

	वापस of_icc_get_by_index(dev, idx);
पूर्ण
EXPORT_SYMBOL_GPL(of_icc_get);

/**
 * icc_set_tag() - set an optional tag on a path
 * @path: the path we want to tag
 * @tag: the tag value
 *
 * This function allows consumers to append a tag to the requests associated
 * with a path, so that a dअगरferent aggregation could be करोne based on this tag.
 */
व्योम icc_set_tag(काष्ठा icc_path *path, u32 tag)
अणु
	पूर्णांक i;

	अगर (!path)
		वापस;

	mutex_lock(&icc_lock);

	क्रम (i = 0; i < path->num_nodes; i++)
		path->reqs[i].tag = tag;

	mutex_unlock(&icc_lock);
पूर्ण
EXPORT_SYMBOL_GPL(icc_set_tag);

/**
 * icc_get_name() - Get name of the icc path
 * @path: reference to the path वापसed by icc_get()
 *
 * This function is used by an पूर्णांकerconnect consumer to get the name of the icc
 * path.
 *
 * Returns a valid poपूर्णांकer on success, or शून्य otherwise.
 */
स्थिर अक्षर *icc_get_name(काष्ठा icc_path *path)
अणु
	अगर (!path)
		वापस शून्य;

	वापस path->name;
पूर्ण
EXPORT_SYMBOL_GPL(icc_get_name);

/**
 * icc_set_bw() - set bandwidth स्थिरraपूर्णांकs on an पूर्णांकerconnect path
 * @path: reference to the path वापसed by icc_get()
 * @avg_bw: average bandwidth in kilobytes per second
 * @peak_bw: peak bandwidth in kilobytes per second
 *
 * This function is used by an पूर्णांकerconnect consumer to express its own needs
 * in terms of bandwidth क्रम a previously requested path between two endpoपूर्णांकs.
 * The requests are aggregated and each node is updated accordingly. The entire
 * path is locked by a mutex to ensure that the set() is completed.
 * The @path can be शून्य when the "interconnects" DT properties is missing,
 * which will mean that no स्थिरraपूर्णांकs will be set.
 *
 * Returns 0 on success, or an appropriate error code otherwise.
 */
पूर्णांक icc_set_bw(काष्ठा icc_path *path, u32 avg_bw, u32 peak_bw)
अणु
	काष्ठा icc_node *node;
	u32 old_avg, old_peak;
	माप_प्रकार i;
	पूर्णांक ret;

	अगर (!path)
		वापस 0;

	अगर (WARN_ON(IS_ERR(path) || !path->num_nodes))
		वापस -EINVAL;

	mutex_lock(&icc_lock);

	old_avg = path->reqs[0].avg_bw;
	old_peak = path->reqs[0].peak_bw;

	क्रम (i = 0; i < path->num_nodes; i++) अणु
		node = path->reqs[i].node;

		/* update the consumer request क्रम this path */
		path->reqs[i].avg_bw = avg_bw;
		path->reqs[i].peak_bw = peak_bw;

		/* aggregate requests क्रम this node */
		aggregate_requests(node);

		trace_icc_set_bw(path, node, i, avg_bw, peak_bw);
	पूर्ण

	ret = apply_स्थिरraपूर्णांकs(path);
	अगर (ret) अणु
		pr_debug("interconnect: error applying constraints (%d)\n",
			 ret);

		क्रम (i = 0; i < path->num_nodes; i++) अणु
			node = path->reqs[i].node;
			path->reqs[i].avg_bw = old_avg;
			path->reqs[i].peak_bw = old_peak;
			aggregate_requests(node);
		पूर्ण
		apply_स्थिरraपूर्णांकs(path);
	पूर्ण

	mutex_unlock(&icc_lock);

	trace_icc_set_bw_end(path, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(icc_set_bw);

अटल पूर्णांक __icc_enable(काष्ठा icc_path *path, bool enable)
अणु
	पूर्णांक i;

	अगर (!path)
		वापस 0;

	अगर (WARN_ON(IS_ERR(path) || !path->num_nodes))
		वापस -EINVAL;

	mutex_lock(&icc_lock);

	क्रम (i = 0; i < path->num_nodes; i++)
		path->reqs[i].enabled = enable;

	mutex_unlock(&icc_lock);

	वापस icc_set_bw(path, path->reqs[0].avg_bw,
			  path->reqs[0].peak_bw);
पूर्ण

पूर्णांक icc_enable(काष्ठा icc_path *path)
अणु
	वापस __icc_enable(path, true);
पूर्ण
EXPORT_SYMBOL_GPL(icc_enable);

पूर्णांक icc_disable(काष्ठा icc_path *path)
अणु
	वापस __icc_enable(path, false);
पूर्ण
EXPORT_SYMBOL_GPL(icc_disable);

/**
 * icc_get() - वापस a handle क्रम path between two endpoपूर्णांकs
 * @dev: the device requesting the path
 * @src_id: source device port id
 * @dst_id: destination device port id
 *
 * This function will search क्रम a path between two endpoपूर्णांकs and वापस an
 * icc_path handle on success. Use icc_put() to release
 * स्थिरraपूर्णांकs when they are not needed anymore.
 * If the पूर्णांकerconnect API is disabled, शून्य is वापसed and the consumer
 * drivers will still build. Drivers are मुक्त to handle this specअगरically,
 * but they करोn't have to.
 *
 * Return: icc_path poपूर्णांकer on success, ERR_PTR() on error or शून्य अगर the
 * पूर्णांकerconnect API is disabled.
 */
काष्ठा icc_path *icc_get(काष्ठा device *dev, स्थिर पूर्णांक src_id, स्थिर पूर्णांक dst_id)
अणु
	काष्ठा icc_node *src, *dst;
	काष्ठा icc_path *path = ERR_PTR(-EPROBE_DEFER);

	mutex_lock(&icc_lock);

	src = node_find(src_id);
	अगर (!src)
		जाओ out;

	dst = node_find(dst_id);
	अगर (!dst)
		जाओ out;

	path = path_find(dev, src, dst);
	अगर (IS_ERR(path)) अणु
		dev_err(dev, "%s: invalid path=%ld\n", __func__, PTR_ERR(path));
		जाओ out;
	पूर्ण

	path->name = kaप्र_लिखो(GFP_KERNEL, "%s-%s", src->name, dst->name);
	अगर (!path->name) अणु
		kमुक्त(path);
		path = ERR_PTR(-ENOMEM);
	पूर्ण
out:
	mutex_unlock(&icc_lock);
	वापस path;
पूर्ण
EXPORT_SYMBOL_GPL(icc_get);

/**
 * icc_put() - release the reference to the icc_path
 * @path: पूर्णांकerconnect path
 *
 * Use this function to release the स्थिरraपूर्णांकs on a path when the path is
 * no दीर्घer needed. The स्थिरraपूर्णांकs will be re-aggregated.
 */
व्योम icc_put(काष्ठा icc_path *path)
अणु
	काष्ठा icc_node *node;
	माप_प्रकार i;
	पूर्णांक ret;

	अगर (!path || WARN_ON(IS_ERR(path)))
		वापस;

	ret = icc_set_bw(path, 0, 0);
	अगर (ret)
		pr_err("%s: error (%d)\n", __func__, ret);

	mutex_lock(&icc_lock);
	क्रम (i = 0; i < path->num_nodes; i++) अणु
		node = path->reqs[i].node;
		hlist_del(&path->reqs[i].req_node);
		अगर (!WARN_ON(!node->provider->users))
			node->provider->users--;
	पूर्ण
	mutex_unlock(&icc_lock);

	kमुक्त_स्थिर(path->name);
	kमुक्त(path);
पूर्ण
EXPORT_SYMBOL_GPL(icc_put);

अटल काष्ठा icc_node *icc_node_create_nolock(पूर्णांक id)
अणु
	काष्ठा icc_node *node;

	/* check अगर node alपढ़ोy exists */
	node = node_find(id);
	अगर (node)
		वापस node;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	id = idr_alloc(&icc_idr, node, id, id + 1, GFP_KERNEL);
	अगर (id < 0) अणु
		WARN(1, "%s: couldn't get idr\n", __func__);
		kमुक्त(node);
		वापस ERR_PTR(id);
	पूर्ण

	node->id = id;

	वापस node;
पूर्ण

/**
 * icc_node_create() - create a node
 * @id: node id
 *
 * Return: icc_node poपूर्णांकer on success, or ERR_PTR() on error
 */
काष्ठा icc_node *icc_node_create(पूर्णांक id)
अणु
	काष्ठा icc_node *node;

	mutex_lock(&icc_lock);

	node = icc_node_create_nolock(id);

	mutex_unlock(&icc_lock);

	वापस node;
पूर्ण
EXPORT_SYMBOL_GPL(icc_node_create);

/**
 * icc_node_destroy() - destroy a node
 * @id: node id
 */
व्योम icc_node_destroy(पूर्णांक id)
अणु
	काष्ठा icc_node *node;

	mutex_lock(&icc_lock);

	node = node_find(id);
	अगर (node) अणु
		idr_हटाओ(&icc_idr, node->id);
		WARN_ON(!hlist_empty(&node->req_list));
	पूर्ण

	mutex_unlock(&icc_lock);

	kमुक्त(node);
पूर्ण
EXPORT_SYMBOL_GPL(icc_node_destroy);

/**
 * icc_link_create() - create a link between two nodes
 * @node: source node id
 * @dst_id: destination node id
 *
 * Create a link between two nodes. The nodes might beदीर्घ to dअगरferent
 * पूर्णांकerconnect providers and the @dst_id node might not exist (अगर the
 * provider driver has not probed yet). So just create the @dst_id node
 * and when the actual provider driver is probed, the rest of the node
 * data is filled.
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक icc_link_create(काष्ठा icc_node *node, स्थिर पूर्णांक dst_id)
अणु
	काष्ठा icc_node *dst;
	काष्ठा icc_node **new;
	पूर्णांक ret = 0;

	अगर (!node->provider)
		वापस -EINVAL;

	mutex_lock(&icc_lock);

	dst = node_find(dst_id);
	अगर (!dst) अणु
		dst = icc_node_create_nolock(dst_id);

		अगर (IS_ERR(dst)) अणु
			ret = PTR_ERR(dst);
			जाओ out;
		पूर्ण
	पूर्ण

	new = kपुनः_स्मृति(node->links,
		       (node->num_links + 1) * माप(*node->links),
		       GFP_KERNEL);
	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	node->links = new;
	node->links[node->num_links++] = dst;

out:
	mutex_unlock(&icc_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(icc_link_create);

/**
 * icc_link_destroy() - destroy a link between two nodes
 * @src: poपूर्णांकer to source node
 * @dst: poपूर्णांकer to destination node
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक icc_link_destroy(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा icc_node **new;
	माप_प्रकार slot;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(src))
		वापस -EINVAL;

	अगर (IS_ERR_OR_शून्य(dst))
		वापस -EINVAL;

	mutex_lock(&icc_lock);

	क्रम (slot = 0; slot < src->num_links; slot++)
		अगर (src->links[slot] == dst)
			अवरोध;

	अगर (WARN_ON(slot == src->num_links)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	src->links[slot] = src->links[--src->num_links];

	new = kपुनः_स्मृति(src->links, src->num_links * माप(*src->links),
		       GFP_KERNEL);
	अगर (new)
		src->links = new;
	अन्यथा
		ret = -ENOMEM;

out:
	mutex_unlock(&icc_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(icc_link_destroy);

/**
 * icc_node_add() - add पूर्णांकerconnect node to पूर्णांकerconnect provider
 * @node: poपूर्णांकer to the पूर्णांकerconnect node
 * @provider: poपूर्णांकer to the पूर्णांकerconnect provider
 */
व्योम icc_node_add(काष्ठा icc_node *node, काष्ठा icc_provider *provider)
अणु
	mutex_lock(&icc_lock);

	node->provider = provider;
	list_add_tail(&node->node_list, &provider->nodes);

	/* get the initial bandwidth values and sync them with hardware */
	अगर (provider->get_bw) अणु
		provider->get_bw(node, &node->init_avg, &node->init_peak);
	पूर्ण अन्यथा अणु
		node->init_avg = पूर्णांक_उच्च;
		node->init_peak = पूर्णांक_उच्च;
	पूर्ण
	node->avg_bw = node->init_avg;
	node->peak_bw = node->init_peak;
	अगर (provider->aggregate)
		provider->aggregate(node, 0, node->init_avg, node->init_peak,
				    &node->avg_bw, &node->peak_bw);
	provider->set(node, node);
	node->avg_bw = 0;
	node->peak_bw = 0;

	mutex_unlock(&icc_lock);
पूर्ण
EXPORT_SYMBOL_GPL(icc_node_add);

/**
 * icc_node_del() - delete पूर्णांकerconnect node from पूर्णांकerconnect provider
 * @node: poपूर्णांकer to the पूर्णांकerconnect node
 */
व्योम icc_node_del(काष्ठा icc_node *node)
अणु
	mutex_lock(&icc_lock);

	list_del(&node->node_list);

	mutex_unlock(&icc_lock);
पूर्ण
EXPORT_SYMBOL_GPL(icc_node_del);

/**
 * icc_nodes_हटाओ() - हटाओ all previously added nodes from provider
 * @provider: the पूर्णांकerconnect provider we are removing nodes from
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक icc_nodes_हटाओ(काष्ठा icc_provider *provider)
अणु
	काष्ठा icc_node *n, *पंचांगp;

	अगर (WARN_ON(IS_ERR_OR_शून्य(provider)))
		वापस -EINVAL;

	list_क्रम_each_entry_safe_reverse(n, पंचांगp, &provider->nodes, node_list) अणु
		icc_node_del(n);
		icc_node_destroy(n->id);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(icc_nodes_हटाओ);

/**
 * icc_provider_add() - add a new पूर्णांकerconnect provider
 * @provider: the पूर्णांकerconnect provider that will be added पूर्णांकo topology
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक icc_provider_add(काष्ठा icc_provider *provider)
अणु
	अगर (WARN_ON(!provider->set))
		वापस -EINVAL;
	अगर (WARN_ON(!provider->xlate && !provider->xlate_extended))
		वापस -EINVAL;

	mutex_lock(&icc_lock);

	INIT_LIST_HEAD(&provider->nodes);
	list_add_tail(&provider->provider_list, &icc_providers);

	mutex_unlock(&icc_lock);

	dev_dbg(provider->dev, "interconnect provider added to topology\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(icc_provider_add);

/**
 * icc_provider_del() - delete previously added पूर्णांकerconnect provider
 * @provider: the पूर्णांकerconnect provider that will be हटाओd from topology
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक icc_provider_del(काष्ठा icc_provider *provider)
अणु
	mutex_lock(&icc_lock);
	अगर (provider->users) अणु
		pr_warn("interconnect provider still has %d users\n",
			provider->users);
		mutex_unlock(&icc_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (!list_empty(&provider->nodes)) अणु
		pr_warn("interconnect provider still has nodes\n");
		mutex_unlock(&icc_lock);
		वापस -EBUSY;
	पूर्ण

	list_del(&provider->provider_list);
	mutex_unlock(&icc_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(icc_provider_del);

अटल पूर्णांक of_count_icc_providers(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक count = 0;

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_bool(child, "#interconnect-cells"))
			count++;
		count += of_count_icc_providers(child);
	पूर्ण

	वापस count;
पूर्ण

व्योम icc_sync_state(काष्ठा device *dev)
अणु
	काष्ठा icc_provider *p;
	काष्ठा icc_node *n;
	अटल पूर्णांक count;

	count++;

	अगर (count < providers_count)
		वापस;

	mutex_lock(&icc_lock);
	synced_state = true;
	list_क्रम_each_entry(p, &icc_providers, provider_list) अणु
		dev_dbg(p->dev, "interconnect provider is in synced state\n");
		list_क्रम_each_entry(n, &p->nodes, node_list) अणु
			अगर (n->init_avg || n->init_peak) अणु
				aggregate_requests(n);
				p->set(n, n);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&icc_lock);
पूर्ण
EXPORT_SYMBOL_GPL(icc_sync_state);

अटल पूर्णांक __init icc_init(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");

	providers_count = of_count_icc_providers(root);
	of_node_put(root);

	icc_debugfs_dir = debugfs_create_dir("interconnect", शून्य);
	debugfs_create_file("interconnect_summary", 0444,
			    icc_debugfs_dir, शून्य, &icc_summary_fops);
	debugfs_create_file("interconnect_graph", 0444,
			    icc_debugfs_dir, शून्य, &icc_graph_fops);
	वापस 0;
पूर्ण

device_initcall(icc_init);

MODULE_AUTHOR("Georgi Djakov <georgi.djakov@linaro.org>");
MODULE_DESCRIPTION("Interconnect Driver Core");
MODULE_LICENSE("GPL v2");
