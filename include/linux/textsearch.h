<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_TEXTSEARCH_H
#घोषणा __LINUX_TEXTSEARCH_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

काष्ठा module;

काष्ठा ts_config;

#घोषणा TS_AUTOLOAD	1 /* Automatically load textsearch modules when needed */
#घोषणा TS_IGNORECASE	2 /* Searches string हाल insensitively */

/**
 * काष्ठा ts_state - search state
 * @offset: offset क्रम next match
 * @cb: control buffer, क्रम persistent variables of get_next_block()
 */
काष्ठा ts_state
अणु
	अचिन्हित पूर्णांक		offset;
	अक्षर			cb[48];
पूर्ण;

/**
 * काष्ठा ts_ops - search module operations
 * @name: name of search algorithm
 * @init: initialization function to prepare a search
 * @find: find the next occurrence of the pattern
 * @destroy: destroy algorithm specअगरic parts of a search configuration
 * @get_pattern: वापस head of pattern
 * @get_pattern_len: वापस length of pattern
 * @owner: module reference to algorithm
 */
काष्ठा ts_ops
अणु
	स्थिर अक्षर		*name;
	काष्ठा ts_config *	(*init)(स्थिर व्योम *, अचिन्हित पूर्णांक, gfp_t, पूर्णांक);
	अचिन्हित पूर्णांक		(*find)(काष्ठा ts_config *,
					काष्ठा ts_state *);
	व्योम			(*destroy)(काष्ठा ts_config *);
	व्योम *			(*get_pattern)(काष्ठा ts_config *);
	अचिन्हित पूर्णांक		(*get_pattern_len)(काष्ठा ts_config *);
	काष्ठा module		*owner;
	काष्ठा list_head	list;
पूर्ण;

/**
 * काष्ठा ts_config - search configuration
 * @ops: operations of chosen algorithm
 * @flags: flags
 * @get_next_block: callback to fetch the next block to search in
 * @finish: callback to finalize a search
 */
काष्ठा ts_config
अणु
	काष्ठा ts_ops		*ops;
	पूर्णांक 			flags;

	/**
	 * @get_next_block: fetch next block of data
	 * @consumed: number of bytes consumed by the caller
	 * @dst: destination buffer
	 * @conf: search configuration
	 * @state: search state
	 *
	 * Called repeatedly until 0 is वापसed. Must assign the
	 * head of the next block of data to &*dst and वापस the length
	 * of the block or 0 अगर at the end. consumed == 0 indicates
	 * a new search. May store/पढ़ो persistent values in state->cb.
	 */
	अचिन्हित पूर्णांक		(*get_next_block)(अचिन्हित पूर्णांक consumed,
						  स्थिर u8 **dst,
						  काष्ठा ts_config *conf,
						  काष्ठा ts_state *state);

	/**
	 * @finish: finalize/clean a series of get_next_block() calls
	 * @conf: search configuration
	 * @state: search state
	 *
	 * Called after the last use of get_next_block(), may be used
	 * to cleanup any leftovers.
	 */
	व्योम			(*finish)(काष्ठा ts_config *conf,
					  काष्ठा ts_state *state);
पूर्ण;

/**
 * textsearch_next - जारी searching क्रम a pattern
 * @conf: search configuration
 * @state: search state
 *
 * Continues a search looking क्रम more occurrences of the pattern.
 * textsearch_find() must be called to find the first occurrence
 * in order to reset the state.
 *
 * Returns the position of the next occurrence of the pattern or
 * अच_पूर्णांक_उच्च अगर not match was found.
 */ 
अटल अंतरभूत अचिन्हित पूर्णांक textsearch_next(काष्ठा ts_config *conf,
					   काष्ठा ts_state *state)
अणु
	अचिन्हित पूर्णांक ret = conf->ops->find(conf, state);

	अगर (conf->finish)
		conf->finish(conf, state);

	वापस ret;
पूर्ण

/**
 * textsearch_find - start searching क्रम a pattern
 * @conf: search configuration
 * @state: search state
 *
 * Returns the position of first occurrence of the pattern or
 * अच_पूर्णांक_उच्च अगर no match was found.
 */ 
अटल अंतरभूत अचिन्हित पूर्णांक textsearch_find(काष्ठा ts_config *conf,
					   काष्ठा ts_state *state)
अणु
	state->offset = 0;
	वापस textsearch_next(conf, state);
पूर्ण

/**
 * textsearch_get_pattern - वापस head of the pattern
 * @conf: search configuration
 */
अटल अंतरभूत व्योम *textsearch_get_pattern(काष्ठा ts_config *conf)
अणु
	वापस conf->ops->get_pattern(conf);
पूर्ण

/**
 * textsearch_get_pattern_len - वापस length of the pattern
 * @conf: search configuration
 */
अटल अंतरभूत अचिन्हित पूर्णांक textsearch_get_pattern_len(काष्ठा ts_config *conf)
अणु
	वापस conf->ops->get_pattern_len(conf);
पूर्ण

बाह्य पूर्णांक textsearch_रेजिस्टर(काष्ठा ts_ops *);
बाह्य पूर्णांक textsearch_unरेजिस्टर(काष्ठा ts_ops *);
बाह्य काष्ठा ts_config *textsearch_prepare(स्थिर अक्षर *, स्थिर व्योम *,
					    अचिन्हित पूर्णांक, gfp_t, पूर्णांक);
बाह्य व्योम textsearch_destroy(काष्ठा ts_config *conf);
बाह्य अचिन्हित पूर्णांक textsearch_find_continuous(काष्ठा ts_config *,
					       काष्ठा ts_state *,
					       स्थिर व्योम *, अचिन्हित पूर्णांक);


#घोषणा TS_PRIV_ALIGNTO	8
#घोषणा TS_PRIV_ALIGN(len) (((len) + TS_PRIV_ALIGNTO-1) & ~(TS_PRIV_ALIGNTO-1))

अटल अंतरभूत काष्ठा ts_config *alloc_ts_config(माप_प्रकार payload,
						gfp_t gfp_mask)
अणु
	काष्ठा ts_config *conf;

	conf = kzalloc(TS_PRIV_ALIGN(माप(*conf)) + payload, gfp_mask);
	अगर (conf == शून्य)
		वापस ERR_PTR(-ENOMEM);

	वापस conf;
पूर्ण

अटल अंतरभूत व्योम *ts_config_priv(काष्ठा ts_config *conf)
अणु
	वापस ((u8 *) conf + TS_PRIV_ALIGN(माप(काष्ठा ts_config)));
पूर्ण

#पूर्ण_अगर
