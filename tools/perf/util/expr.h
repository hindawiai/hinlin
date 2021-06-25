<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PARSE_CTX_H
#घोषणा PARSE_CTX_H 1

// There are fixes that need to land upstream beक्रमe we can use libbpf's headers,
// क्रम now use our copy unconditionally, since the data काष्ठाures at this poपूर्णांक
// are exactly the same, no problem.
//#अगर_घोषित HAVE_LIBBPF_SUPPORT
//#समावेश <bpf/hashmap.h>
//#अन्यथा
#समावेश "util/hashmap.h"
//#पूर्ण_अगर

काष्ठा metric_ref;

काष्ठा expr_id अणु
	अक्षर		*id;
	काष्ठा expr_id	*parent;
पूर्ण;

काष्ठा expr_parse_ctx अणु
	काष्ठा hashmap	 ids;
	काष्ठा expr_id	*parent;
पूर्ण;

काष्ठा expr_id_data;

काष्ठा expr_scanner_ctx अणु
	पूर्णांक start_token;
	पूर्णांक runसमय;
पूर्ण;

व्योम expr__ctx_init(काष्ठा expr_parse_ctx *ctx);
व्योम expr__ctx_clear(काष्ठा expr_parse_ctx *ctx);
व्योम expr__del_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id);
पूर्णांक expr__add_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id);
पूर्णांक expr__add_id_val(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id, द्विगुन val);
पूर्णांक expr__add_ref(काष्ठा expr_parse_ctx *ctx, काष्ठा metric_ref *ref);
पूर्णांक expr__get_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id,
		 काष्ठा expr_id_data **data);
पूर्णांक expr__resolve_id(काष्ठा expr_parse_ctx *ctx, स्थिर अक्षर *id,
		     काष्ठा expr_id_data **datap);
पूर्णांक expr__parse(द्विगुन *final_val, काष्ठा expr_parse_ctx *ctx,
		स्थिर अक्षर *expr, पूर्णांक runसमय);
पूर्णांक expr__find_other(स्थिर अक्षर *expr, स्थिर अक्षर *one,
		काष्ठा expr_parse_ctx *ids, पूर्णांक runसमय);

द्विगुन expr_id_data__value(स्थिर काष्ठा expr_id_data *data);
काष्ठा expr_id *expr_id_data__parent(काष्ठा expr_id_data *data);

#पूर्ण_अगर
