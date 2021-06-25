<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lib/textsearch.c	Generic text search पूर्णांकerface
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 * 		Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * ==========================================================================
 */

/**
 * DOC: ts_पूर्णांकro
 * INTRODUCTION
 *
 *   The textsearch infraकाष्ठाure provides text searching facilities क्रम
 *   both linear and non-linear data. Inभागidual search algorithms are
 *   implemented in modules and chosen by the user.
 *
 * ARCHITECTURE
 *
 * .. code-block:: none
 *
 *     User
 *     +----------------+
 *     |        finish()|<--------------(6)-----------------+
 *     |get_next_block()|<--------------(5)---------------+ |
 *     |                |                     Algorithm   | |
 *     |                |                    +------------------------------+
 *     |                |                    |  init()   find()   destroy() |
 *     |                |                    +------------------------------+
 *     |                |       Core API           ^       ^          ^
 *     |                |      +---------------+  (2)     (4)        (8)
 *     |             (1)|----->| prepare()     |---+       |          |
 *     |             (3)|----->| find()/next() |-----------+          |
 *     |             (7)|----->| destroy()     |----------------------+
 *     +----------------+      +---------------+
 *
 *   (1) User configures a search by calling textsearch_prepare() specअगरying
 *       the search parameters such as the pattern and algorithm name.
 *   (2) Core requests the algorithm to allocate and initialize a search
 *       configuration according to the specअगरied parameters.
 *   (3) User starts the search(es) by calling textsearch_find() or
 *       textsearch_next() to fetch subsequent occurrences. A state variable
 *       is provided to the algorithm to store persistent variables.
 *   (4) Core eventually resets the search offset and क्रमwards the find()
 *       request to the algorithm.
 *   (5) Algorithm calls get_next_block() provided by the user continuously
 *       to fetch the data to be searched in block by block.
 *   (6) Algorithm invokes finish() after the last call to get_next_block
 *       to clean up any leftovers from get_next_block. (Optional)
 *   (7) User destroys the configuration by calling textsearch_destroy().
 *   (8) Core notअगरies the algorithm to destroy algorithm specअगरic
 *       allocations. (Optional)
 *
 * USAGE
 *
 *   Beक्रमe a search can be perक्रमmed, a configuration must be created
 *   by calling textsearch_prepare() specअगरying the searching algorithm,
 *   the pattern to look क्रम and flags. As a flag, you can set TS_IGNORECASE
 *   to perक्रमm हाल insensitive matching. But it might slow करोwn
 *   perक्रमmance of algorithm, so you should use it at own your risk.
 *   The वापसed configuration may then be used क्रम an arbitrary
 *   amount of बार and even in parallel as दीर्घ as a separate काष्ठा
 *   ts_state variable is provided to every instance.
 *
 *   The actual search is perक्रमmed by either calling
 *   textsearch_find_continuous() क्रम linear data or by providing
 *   an own get_next_block() implementation and
 *   calling textsearch_find(). Both functions वापस
 *   the position of the first occurrence of the pattern or अच_पूर्णांक_उच्च अगर
 *   no match was found. Subsequent occurrences can be found by calling
 *   textsearch_next() regardless of the linearity of the data.
 *
 *   Once you're करोne using a configuration it must be given back via
 *   textsearch_destroy.
 *
 * EXAMPLE::
 *
 *   पूर्णांक pos;
 *   काष्ठा ts_config *conf;
 *   काष्ठा ts_state state;
 *   स्थिर अक्षर *pattern = "chicken";
 *   स्थिर अक्षर *example = "We dance the funky chicken";
 *
 *   conf = textsearch_prepare("kmp", pattern, म_माप(pattern),
 *                             GFP_KERNEL, TS_AUTOLOAD);
 *   अगर (IS_ERR(conf)) अणु
 *       err = PTR_ERR(conf);
 *       जाओ errout;
 *   पूर्ण
 *
 *   pos = textsearch_find_continuous(conf, &state, example, म_माप(example));
 *   अगर (pos != अच_पूर्णांक_उच्च)
 *       panic("Oh my god, dancing chickens at %d\n", pos);
 *
 *   textsearch_destroy(conf);
 */
/* ========================================================================== */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/err.h>
#समावेश <linux/textsearch.h>
#समावेश <linux/slab.h>

अटल LIST_HEAD(ts_ops);
अटल DEFINE_SPINLOCK(ts_mod_lock);

अटल अंतरभूत काष्ठा ts_ops *lookup_ts_algo(स्थिर अक्षर *name)
अणु
	काष्ठा ts_ops *o;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(o, &ts_ops, list) अणु
		अगर (!म_भेद(name, o->name)) अणु
			अगर (!try_module_get(o->owner))
				o = शून्य;
			rcu_पढ़ो_unlock();
			वापस o;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

/**
 * textsearch_रेजिस्टर - रेजिस्टर a textsearch module
 * @ops: operations lookup table
 *
 * This function must be called by textsearch modules to announce
 * their presence. The specअगरied &@ops must have %name set to a
 * unique identअगरier and the callbacks find(), init(), get_pattern(),
 * and get_pattern_len() must be implemented.
 *
 * Returns 0 or -EEXISTS अगर another module has alपढ़ोy रेजिस्टरed
 * with same name.
 */
पूर्णांक textsearch_रेजिस्टर(काष्ठा ts_ops *ops)
अणु
	पूर्णांक err = -EEXIST;
	काष्ठा ts_ops *o;

	अगर (ops->name == शून्य || ops->find == शून्य || ops->init == शून्य ||
	    ops->get_pattern == शून्य || ops->get_pattern_len == शून्य)
		वापस -EINVAL;

	spin_lock(&ts_mod_lock);
	list_क्रम_each_entry(o, &ts_ops, list) अणु
		अगर (!म_भेद(ops->name, o->name))
			जाओ errout;
	पूर्ण

	list_add_tail_rcu(&ops->list, &ts_ops);
	err = 0;
errout:
	spin_unlock(&ts_mod_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(textsearch_रेजिस्टर);

/**
 * textsearch_unरेजिस्टर - unरेजिस्टर a textsearch module
 * @ops: operations lookup table
 *
 * This function must be called by textsearch modules to announce
 * their disappearance क्रम examples when the module माला_लो unloaded.
 * The &ops parameter must be the same as the one during the
 * registration.
 *
 * Returns 0 on success or -ENOENT अगर no matching textsearch
 * registration was found.
 */
पूर्णांक textsearch_unरेजिस्टर(काष्ठा ts_ops *ops)
अणु
	पूर्णांक err = 0;
	काष्ठा ts_ops *o;

	spin_lock(&ts_mod_lock);
	list_क्रम_each_entry(o, &ts_ops, list) अणु
		अगर (o == ops) अणु
			list_del_rcu(&o->list);
			जाओ out;
		पूर्ण
	पूर्ण

	err = -ENOENT;
out:
	spin_unlock(&ts_mod_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(textsearch_unरेजिस्टर);

काष्ठा ts_linear_state
अणु
	अचिन्हित पूर्णांक	len;
	स्थिर व्योम	*data;
पूर्ण;

अटल अचिन्हित पूर्णांक get_linear_data(अचिन्हित पूर्णांक consumed, स्थिर u8 **dst,
				    काष्ठा ts_config *conf,
				    काष्ठा ts_state *state)
अणु
	काष्ठा ts_linear_state *st = (काष्ठा ts_linear_state *) state->cb;

	अगर (likely(consumed < st->len)) अणु
		*dst = st->data + consumed;
		वापस st->len - consumed;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * textsearch_find_continuous - search a pattern in continuous/linear data
 * @conf: search configuration
 * @state: search state
 * @data: data to search in
 * @len: length of data
 *
 * A simplअगरied version of textsearch_find() क्रम continuous/linear data.
 * Call textsearch_next() to retrieve subsequent matches.
 *
 * Returns the position of first occurrence of the pattern or
 * %अच_पूर्णांक_उच्च अगर no occurrence was found.
 */
अचिन्हित पूर्णांक textsearch_find_continuous(काष्ठा ts_config *conf,
					काष्ठा ts_state *state,
					स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ts_linear_state *st = (काष्ठा ts_linear_state *) state->cb;

	conf->get_next_block = get_linear_data;
	st->data = data;
	st->len = len;

	वापस textsearch_find(conf, state);
पूर्ण
EXPORT_SYMBOL(textsearch_find_continuous);

/**
 * textsearch_prepare - Prepare a search
 * @algo: name of search algorithm
 * @pattern: pattern data
 * @len: length of pattern
 * @gfp_mask: allocation mask
 * @flags: search flags
 *
 * Looks up the search algorithm module and creates a new textsearch
 * configuration क्रम the specअगरied pattern.
 *
 * Note: The क्रमmat of the pattern may not be compatible between
 *       the various search algorithms.
 *
 * Returns a new textsearch configuration according to the specअगरied
 * parameters or a ERR_PTR(). If a zero length pattern is passed, this
 * function वापसs EINVAL.
 */
काष्ठा ts_config *textsearch_prepare(स्थिर अक्षर *algo, स्थिर व्योम *pattern,
				     अचिन्हित पूर्णांक len, gfp_t gfp_mask, पूर्णांक flags)
अणु
	पूर्णांक err = -ENOENT;
	काष्ठा ts_config *conf;
	काष्ठा ts_ops *ops;
	
	अगर (len == 0)
		वापस ERR_PTR(-EINVAL);

	ops = lookup_ts_algo(algo);
#अगर_घोषित CONFIG_MODULES
	/*
	 * Why not always स्वतःload you may ask. Some users are
	 * in a situation where requesting a module may deadlock,
	 * especially when the module is located on a NFS mount.
	 */
	अगर (ops == शून्य && flags & TS_AUTOLOAD) अणु
		request_module("ts_%s", algo);
		ops = lookup_ts_algo(algo);
	पूर्ण
#पूर्ण_अगर

	अगर (ops == शून्य)
		जाओ errout;

	conf = ops->init(pattern, len, gfp_mask, flags);
	अगर (IS_ERR(conf)) अणु
		err = PTR_ERR(conf);
		जाओ errout;
	पूर्ण

	conf->ops = ops;
	वापस conf;

errout:
	अगर (ops)
		module_put(ops->owner);
		
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(textsearch_prepare);

/**
 * textsearch_destroy - destroy a search configuration
 * @conf: search configuration
 *
 * Releases all references of the configuration and मुक्तs
 * up the memory.
 */
व्योम textsearch_destroy(काष्ठा ts_config *conf)
अणु
	अगर (conf->ops) अणु
		अगर (conf->ops->destroy)
			conf->ops->destroy(conf);
		module_put(conf->ops->owner);
	पूर्ण

	kमुक्त(conf);
पूर्ण
EXPORT_SYMBOL(textsearch_destroy);
