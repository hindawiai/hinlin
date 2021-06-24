<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_MDESC_H
#घोषणा _SPARC64_MDESC_H

#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/prom.h>

काष्ठा mdesc_handle;

/* Machine description operations are to be surrounded by grab and
 * release calls.  The mdesc_handle वापसed from the grab is
 * the first argument to all of the operational calls that work
 * on mdescs.
 */
काष्ठा mdesc_handle *mdesc_grab(व्योम);
व्योम mdesc_release(काष्ठा mdesc_handle *);

#घोषणा MDESC_NODE_शून्य		(~(u64)0)
#घोषणा MDESC_MAX_STR_LEN	256

u64 mdesc_node_by_name(काष्ठा mdesc_handle *handle,
		       u64 from_node, स्थिर अक्षर *name);
#घोषणा mdesc_क्रम_each_node_by_name(__hdl, __node, __name) \
	क्रम (__node = mdesc_node_by_name(__hdl, MDESC_NODE_शून्य, __name); \
	     (__node) != MDESC_NODE_शून्य; \
	     __node = mdesc_node_by_name(__hdl, __node, __name))

/* Access to property values वापसed from mdesc_get_property() are
 * only valid inside of a mdesc_grab()/mdesc_release() sequence.
 * Once mdesc_release() is called, the memory backed up by these
 * poपूर्णांकers may reference मुक्तd up memory.
 *
 * Thereक्रमe callers must make copies of any property values
 * they need.
 *
 * These same rules apply to mdesc_node_name().
 */
स्थिर व्योम *mdesc_get_property(काष्ठा mdesc_handle *handle,
			       u64 node, स्थिर अक्षर *name, पूर्णांक *lenp);
स्थिर अक्षर *mdesc_node_name(काष्ठा mdesc_handle *hp, u64 node);

/* MD arc iteration, the standard sequence is:
 *
 *	अचिन्हित दीर्घ arc;
 *	mdesc_क्रम_each_arc(arc, handle, node, MDESC_ARC_TYPE_अणुFWD,BACKपूर्ण) अणु
 *		अचिन्हित दीर्घ target = mdesc_arc_target(handle, arc);
 *		...
 *	पूर्ण
 */

#घोषणा MDESC_ARC_TYPE_FWD	"fwd"
#घोषणा MDESC_ARC_TYPE_BACK	"back"

u64 mdesc_next_arc(काष्ठा mdesc_handle *handle, u64 from,
		   स्थिर अक्षर *arc_type);
#घोषणा mdesc_क्रम_each_arc(__arc, __hdl, __node, __type) \
	क्रम (__arc = mdesc_next_arc(__hdl, __node, __type); \
	     (__arc) != MDESC_NODE_शून्य; \
	     __arc = mdesc_next_arc(__hdl, __arc, __type))

u64 mdesc_arc_target(काष्ठा mdesc_handle *hp, u64 arc);

व्योम mdesc_update(व्योम);

काष्ठा mdesc_notअगरier_client अणु
	व्योम (*add)(काष्ठा mdesc_handle *handle, u64 node,
		    स्थिर अक्षर *node_name);
	व्योम (*हटाओ)(काष्ठा mdesc_handle *handle, u64 node,
		       स्थिर अक्षर *node_name);
	स्थिर अक्षर			*node_name;
	काष्ठा mdesc_notअगरier_client	*next;
पूर्ण;

व्योम mdesc_रेजिस्टर_notअगरier(काष्ठा mdesc_notअगरier_client *client);

जोड़ md_node_info अणु
	काष्ठा vdev_port अणु
		u64 id;				/* id */
		u64 parent_cfg_hdl;		/* parent config handle */
		स्थिर अक्षर *name;		/* name (property) */
	पूर्ण vdev_port;
	काष्ठा ds_port अणु
		u64 id;				/* id */
	पूर्ण ds_port;
पूर्ण;

u64 mdesc_get_node(काष्ठा mdesc_handle *hp, स्थिर अक्षर *node_name,
		   जोड़ md_node_info *node_info);
पूर्णांक mdesc_get_node_info(काष्ठा mdesc_handle *hp, u64 node,
			स्थिर अक्षर *node_name, जोड़ md_node_info *node_info);

व्योम mdesc_fill_in_cpu_data(cpumask_t *mask);
व्योम mdesc_populate_present_mask(cpumask_t *mask);
व्योम mdesc_get_page_sizes(cpumask_t *mask, अचिन्हित दीर्घ *pgsz_mask);

व्योम sun4v_mdesc_init(व्योम);

#पूर्ण_अगर
