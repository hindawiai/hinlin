<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "metricgroup.h"
#समावेश "debug.h"
#समावेश "expr.h"
#समावेश "expr-bison.h"
#समावेश "expr-flex.h"
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <प्रकार.स>

#अगर_घोषित PARSER_DEBUG
बाह्य पूर्णांक expr_debug;
#पूर्ण_अगर

काष्ठा expr_id_data अणु
	जोड़ अणु
		द्विगुन val;
		काष्ठा अणु
			द्विगुन val;
			स्थिर अक्षर *metric_name;
			स्थिर अक्षर *metric_expr;
		पूर्ण ref;
		काष्ठा expr_id	*parent;
	पूर्ण;

	क्रमागत अणु
		/* Holding a द्विगुन value. */
		EXPR_ID_DATA__VALUE,
		/* Reference to another metric. */
		EXPR_ID_DATA__REF,
		/* A reference but the value has been computed. */
		EXPR_ID_DATA__REF_VALUE,
		/* A parent is remembered क्रम the recursion check. */
		EXPR_ID_DATA__PARENT,
	पूर्ण kind;
पूर्ण;

अटल माप_प्रकार key_hash(स्थिर व्योम *key, व्योम *ctx __maybe_unused)
अणु
	स्थिर अक्षर *str = (स्थिर अक्षर *)key;
	माप_प्रकार hash = 0;

	जबतक (*str != '\0') अणु
		hash *= 31;
		hash += *str;
		str++;
	पूर्ण
	वापस hash;
पूर्ण

अटल bool key_equal(स्थिर व्योम *key1, स्थिर व्योम *key2,
		    व्योम *ctx __maybe_unused)
अणु
	वापस !म_भेद((स्थिर अक्षर *)key1, (स्थिर अक्षर *)key2);
पूर्ण

/* Caller must make sure id is allocated */
पूर्णांक expr__add_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id)
अणु
	काष्ठा expr_id_data *data_ptr = शून्य, *old_data = शून्य;
	अक्षर *old_key = शून्य;
	पूर्णांक ret;

	data_ptr = दो_स्मृति(माप(*data_ptr));
	अगर (!data_ptr)
		वापस -ENOMEM;

	data_ptr->parent = ctx->parent;
	data_ptr->kind = EXPR_ID_DATA__PARENT;

	ret = hashmap__set(&ctx->ids, id, data_ptr,
			   (स्थिर व्योम **)&old_key, (व्योम **)&old_data);
	अगर (ret)
		मुक्त(data_ptr);
	मुक्त(old_key);
	मुक्त(old_data);
	वापस ret;
पूर्ण

/* Caller must make sure id is allocated */
पूर्णांक expr__add_id_val(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id, द्विगुन val)
अणु
	काष्ठा expr_id_data *data_ptr = शून्य, *old_data = शून्य;
	अक्षर *old_key = शून्य;
	पूर्णांक ret;

	data_ptr = दो_स्मृति(माप(*data_ptr));
	अगर (!data_ptr)
		वापस -ENOMEM;
	data_ptr->val = val;
	data_ptr->kind = EXPR_ID_DATA__VALUE;

	ret = hashmap__set(&ctx->ids, id, data_ptr,
			   (स्थिर व्योम **)&old_key, (व्योम **)&old_data);
	अगर (ret)
		मुक्त(data_ptr);
	मुक्त(old_key);
	मुक्त(old_data);
	वापस ret;
पूर्ण

पूर्णांक expr__add_ref(काष्ठा expr_parse_ctx *ctx, काष्ठा metric_ref *ref)
अणु
	काष्ठा expr_id_data *data_ptr = शून्य, *old_data = शून्य;
	अक्षर *old_key = शून्य;
	अक्षर *name, *p;
	पूर्णांक ret;

	data_ptr = zalloc(माप(*data_ptr));
	अगर (!data_ptr)
		वापस -ENOMEM;

	name = strdup(ref->metric_name);
	अगर (!name) अणु
		मुक्त(data_ptr);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The jevents tool converts all metric expressions
	 * to lowerहाल, including metric references, hence
	 * we need to add lowerहाल name क्रम metric, so it's
	 * properly found.
	 */
	क्रम (p = name; *p; p++)
		*p = छोटे(*p);

	/*
	 * Intentionally passing just स्थिर अक्षर poपूर्णांकers,
	 * originally from 'struct pmu_event' object.
	 * We करोn't need to change them, so there's no
	 * need to create our own copy.
	 */
	data_ptr->ref.metric_name = ref->metric_name;
	data_ptr->ref.metric_expr = ref->metric_expr;
	data_ptr->kind = EXPR_ID_DATA__REF;

	ret = hashmap__set(&ctx->ids, name, data_ptr,
			   (स्थिर व्योम **)&old_key, (व्योम **)&old_data);
	अगर (ret)
		मुक्त(data_ptr);

	pr_debug2("adding ref metric %s: %s\n",
		  ref->metric_name, ref->metric_expr);

	मुक्त(old_key);
	मुक्त(old_data);
	वापस ret;
पूर्ण

पूर्णांक expr__get_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id,
		 काष्ठा expr_id_data **data)
अणु
	वापस hashmap__find(&ctx->ids, id, (व्योम **)data) ? 0 : -1;
पूर्ण

पूर्णांक expr__resolve_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id,
		     काष्ठा expr_id_data **datap)
अणु
	काष्ठा expr_id_data *data;

	अगर (expr__get_id(ctx, id, datap) || !*datap) अणु
		pr_debug("%s not found\n", id);
		वापस -1;
	पूर्ण

	data = *datap;

	चयन (data->kind) अणु
	हाल EXPR_ID_DATA__VALUE:
		pr_debug2("lookup(%s): val %f\n", id, data->val);
		अवरोध;
	हाल EXPR_ID_DATA__PARENT:
		pr_debug2("lookup(%s): parent %s\n", id, data->parent->id);
		अवरोध;
	हाल EXPR_ID_DATA__REF:
		pr_debug2("lookup(%s): ref metric name %s\n", id,
			data->ref.metric_name);
		pr_debug("processing metric: %s ENTRY\n", id);
		data->kind = EXPR_ID_DATA__REF_VALUE;
		अगर (expr__parse(&data->ref.val, ctx, data->ref.metric_expr, 1)) अणु
			pr_debug("%s failed to count\n", id);
			वापस -1;
		पूर्ण
		pr_debug("processing metric: %s EXIT: %f\n", id, data->val);
		अवरोध;
	हाल EXPR_ID_DATA__REF_VALUE:
		pr_debug2("lookup(%s): ref val %f metric name %s\n", id,
			data->ref.val, data->ref.metric_name);
		अवरोध;
	शेष:
		निश्चित(0);  /* Unreachable. */
	पूर्ण

	वापस 0;
पूर्ण

व्योम expr__del_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id)
अणु
	काष्ठा expr_id_data *old_val = शून्य;
	अक्षर *old_key = शून्य;

	hashmap__delete(&ctx->ids, id,
			(स्थिर व्योम **)&old_key, (व्योम **)&old_val);
	मुक्त(old_key);
	मुक्त(old_val);
पूर्ण

व्योम expr__ctx_init(काष्ठा expr_parse_ctx *ctx)
अणु
	hashmap__init(&ctx->ids, key_hash, key_equal, शून्य);
पूर्ण

व्योम expr__ctx_clear(काष्ठा expr_parse_ctx *ctx)
अणु
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;

	hashmap__क्रम_each_entry((&ctx->ids), cur, bkt) अणु
		मुक्त((अक्षर *)cur->key);
		मुक्त(cur->value);
	पूर्ण
	hashmap__clear(&ctx->ids);
पूर्ण

अटल पूर्णांक
__expr__parse(द्विगुन *val, काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *expr,
	      पूर्णांक start, पूर्णांक runसमय)
अणु
	काष्ठा expr_scanner_ctx scanner_ctx = अणु
		.start_token = start,
		.runसमय = runसमय,
	पूर्ण;
	YY_BUFFER_STATE buffer;
	व्योम *scanner;
	पूर्णांक ret;

	pr_debug2("parsing metric: %s\n", expr);

	ret = expr_lex_init_extra(&scanner_ctx, &scanner);
	अगर (ret)
		वापस ret;

	buffer = expr__scan_string(expr, scanner);

#अगर_घोषित PARSER_DEBUG
	expr_debug = 1;
	expr_set_debug(1, scanner);
#पूर्ण_अगर

	ret = expr_parse(val, ctx, scanner);

	expr__flush_buffer(buffer, scanner);
	expr__delete_buffer(buffer, scanner);
	expr_lex_destroy(scanner);
	वापस ret;
पूर्ण

पूर्णांक expr__parse(द्विगुन *final_val, काष्ठा expr_parse_ctx *ctx,
		स्थिर अक्षर *expr, पूर्णांक runसमय)
अणु
	वापस __expr__parse(final_val, ctx, expr, EXPR_PARSE, runसमय) ? -1 : 0;
पूर्ण

पूर्णांक expr__find_other(स्थिर अक्षर *expr, स्थिर अक्षर *one,
		     काष्ठा expr_parse_ctx *ctx, पूर्णांक runसमय)
अणु
	पूर्णांक ret = __expr__parse(शून्य, ctx, expr, EXPR_OTHER, runसमय);

	अगर (one)
		expr__del_id(ctx, one);

	वापस ret;
पूर्ण

द्विगुन expr_id_data__value(स्थिर काष्ठा expr_id_data *data)
अणु
	अगर (data->kind == EXPR_ID_DATA__VALUE)
		वापस data->val;
	निश्चित(data->kind == EXPR_ID_DATA__REF_VALUE);
	वापस data->ref.val;
पूर्ण

काष्ठा expr_id *expr_id_data__parent(काष्ठा expr_id_data *data)
अणु
	निश्चित(data->kind == EXPR_ID_DATA__PARENT);
	वापस data->parent;
पूर्ण
