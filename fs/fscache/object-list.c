<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Global fscache object list मुख्यtainer and viewer
 *
 * Copyright (C) 2009 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL COOKIE
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/key.h>
#समावेश <keys/user-type.h>
#समावेश "internal.h"

अटल काष्ठा rb_root fscache_object_list;
अटल DEFINE_RWLOCK(fscache_object_list_lock);

काष्ठा fscache_objlist_data अणु
	अचिन्हित दीर्घ	config;		/* display configuration */
#घोषणा FSCACHE_OBJLIST_CONFIG_KEY	0x00000001	/* show object keys */
#घोषणा FSCACHE_OBJLIST_CONFIG_AUX	0x00000002	/* show object auxdata */
#घोषणा FSCACHE_OBJLIST_CONFIG_COOKIE	0x00000004	/* show objects with cookies */
#घोषणा FSCACHE_OBJLIST_CONFIG_NOCOOKIE	0x00000008	/* show objects without cookies */
#घोषणा FSCACHE_OBJLIST_CONFIG_BUSY	0x00000010	/* show busy objects */
#घोषणा FSCACHE_OBJLIST_CONFIG_IDLE	0x00000020	/* show idle objects */
#घोषणा FSCACHE_OBJLIST_CONFIG_PENDWR	0x00000040	/* show objects with pending ग_लिखोs */
#घोषणा FSCACHE_OBJLIST_CONFIG_NOPENDWR	0x00000080	/* show objects without pending ग_लिखोs */
#घोषणा FSCACHE_OBJLIST_CONFIG_READS	0x00000100	/* show objects with active पढ़ोs */
#घोषणा FSCACHE_OBJLIST_CONFIG_NOREADS	0x00000200	/* show objects without active पढ़ोs */
#घोषणा FSCACHE_OBJLIST_CONFIG_EVENTS	0x00000400	/* show objects with events */
#घोषणा FSCACHE_OBJLIST_CONFIG_NOEVENTS	0x00000800	/* show objects without no events */
#घोषणा FSCACHE_OBJLIST_CONFIG_WORK	0x00001000	/* show objects with work */
#घोषणा FSCACHE_OBJLIST_CONFIG_NOWORK	0x00002000	/* show objects without work */
पूर्ण;

/*
 * Add an object to the object list
 * - we use the address of the fscache_object काष्ठाure as the key पूर्णांकo the
 *   tree
 */
व्योम fscache_objlist_add(काष्ठा fscache_object *obj)
अणु
	काष्ठा fscache_object *xobj;
	काष्ठा rb_node **p = &fscache_object_list.rb_node, *parent = शून्य;

	ASSERT(RB_EMPTY_NODE(&obj->objlist_link));

	ग_लिखो_lock(&fscache_object_list_lock);

	जबतक (*p) अणु
		parent = *p;
		xobj = rb_entry(parent, काष्ठा fscache_object, objlist_link);

		अगर (obj < xobj)
			p = &(*p)->rb_left;
		अन्यथा अगर (obj > xobj)
			p = &(*p)->rb_right;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&obj->objlist_link, parent, p);
	rb_insert_color(&obj->objlist_link, &fscache_object_list);

	ग_लिखो_unlock(&fscache_object_list_lock);
पूर्ण

/*
 * Remove an object from the object list.
 */
व्योम fscache_objlist_हटाओ(काष्ठा fscache_object *obj)
अणु
	अगर (RB_EMPTY_NODE(&obj->objlist_link))
		वापस;

	ग_लिखो_lock(&fscache_object_list_lock);

	BUG_ON(RB_EMPTY_ROOT(&fscache_object_list));
	rb_erase(&obj->objlist_link, &fscache_object_list);

	ग_लिखो_unlock(&fscache_object_list_lock);
पूर्ण

/*
 * find the object in the tree on or after the specअगरied index
 */
अटल काष्ठा fscache_object *fscache_objlist_lookup(loff_t *_pos)
अणु
	काष्ठा fscache_object *pobj, *obj = शून्य, *minobj = शून्य;
	काष्ठा rb_node *p;
	अचिन्हित दीर्घ pos;

	अगर (*_pos >= (अचिन्हित दीर्घ) ERR_PTR(-ENOENT))
		वापस शून्य;
	pos = *_pos;

	/* banners (can't represent line 0 by pos 0 as that would involve
	 * वापसing a शून्य poपूर्णांकer) */
	अगर (pos == 0)
		वापस (काष्ठा fscache_object *)(दीर्घ)++(*_pos);
	अगर (pos < 3)
		वापस (काष्ठा fscache_object *)pos;

	pobj = (काष्ठा fscache_object *)pos;
	p = fscache_object_list.rb_node;
	जबतक (p) अणु
		obj = rb_entry(p, काष्ठा fscache_object, objlist_link);
		अगर (pobj < obj) अणु
			अगर (!minobj || minobj > obj)
				minobj = obj;
			p = p->rb_left;
		पूर्ण अन्यथा अगर (pobj > obj) अणु
			p = p->rb_right;
		पूर्ण अन्यथा अणु
			minobj = obj;
			अवरोध;
		पूर्ण
		obj = शून्य;
	पूर्ण

	अगर (!minobj)
		*_pos = (अचिन्हित दीर्घ) ERR_PTR(-ENOENT);
	अन्यथा अगर (minobj != obj)
		*_pos = (अचिन्हित दीर्घ) minobj;
	वापस minobj;
पूर्ण

/*
 * set up the iterator to start पढ़ोing from the first line
 */
अटल व्योम *fscache_objlist_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(&fscache_object_list_lock)
अणु
	पढ़ो_lock(&fscache_object_list_lock);
	वापस fscache_objlist_lookup(_pos);
पूर्ण

/*
 * move to the next line
 */
अटल व्योम *fscache_objlist_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	(*_pos)++;
	वापस fscache_objlist_lookup(_pos);
पूर्ण

/*
 * clean up after पढ़ोing
 */
अटल व्योम fscache_objlist_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&fscache_object_list_lock)
अणु
	पढ़ो_unlock(&fscache_object_list_lock);
पूर्ण

/*
 * display an object
 */
अटल पूर्णांक fscache_objlist_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fscache_objlist_data *data = m->निजी;
	काष्ठा fscache_object *obj = v;
	काष्ठा fscache_cookie *cookie;
	अचिन्हित दीर्घ config = data->config;
	अक्षर _type[3], *type;
	u8 *p;

	अगर ((अचिन्हित दीर्घ) v == 1) अणु
		seq_माला_दो(m, "OBJECT   PARENT   STAT CHLDN OPS OOP IPR EX READS"
			 " EM EV FL S"
			 " | NETFS_COOKIE_DEF TY FL NETFS_DATA");
		अगर (config & (FSCACHE_OBJLIST_CONFIG_KEY |
			      FSCACHE_OBJLIST_CONFIG_AUX))
			seq_माला_दो(m, "       ");
		अगर (config & FSCACHE_OBJLIST_CONFIG_KEY)
			seq_माला_दो(m, "OBJECT_KEY");
		अगर ((config & (FSCACHE_OBJLIST_CONFIG_KEY |
			       FSCACHE_OBJLIST_CONFIG_AUX)) ==
		    (FSCACHE_OBJLIST_CONFIG_KEY | FSCACHE_OBJLIST_CONFIG_AUX))
			seq_माला_दो(m, ", ");
		अगर (config & FSCACHE_OBJLIST_CONFIG_AUX)
			seq_माला_दो(m, "AUX_DATA");
		seq_माला_दो(m, "\n");
		वापस 0;
	पूर्ण

	अगर ((अचिन्हित दीर्घ) v == 2) अणु
		seq_माला_दो(m, "======== ======== ==== ===== === === === == ====="
			 " == == == ="
			 " | ================ == == ================");
		अगर (config & (FSCACHE_OBJLIST_CONFIG_KEY |
			      FSCACHE_OBJLIST_CONFIG_AUX))
			seq_माला_दो(m, " ================");
		seq_माला_दो(m, "\n");
		वापस 0;
	पूर्ण

	/* filter out any unwanted objects */
#घोषणा FILTER(criterion, _yes, _no)					\
	करो अणु								\
		अचिन्हित दीर्घ yes = FSCACHE_OBJLIST_CONFIG_##_yes;	\
		अचिन्हित दीर्घ no = FSCACHE_OBJLIST_CONFIG_##_no;	\
		अगर (criterion) अणु					\
			अगर (!(config & yes))				\
				वापस 0;				\
		पूर्ण अन्यथा अणु						\
			अगर (!(config & no))				\
				वापस 0;				\
		पूर्ण							\
	पूर्ण जबतक(0)

	cookie = obj->cookie;
	अगर (~config) अणु
		FILTER(cookie->def,
		       COOKIE, NOCOOKIE);
		FILTER(fscache_object_is_active(obj) ||
		       obj->n_ops != 0 ||
		       obj->n_obj_ops != 0 ||
		       obj->flags ||
		       !list_empty(&obj->dependents),
		       BUSY, IDLE);
		FILTER(test_bit(FSCACHE_OBJECT_PENDING_WRITE, &obj->flags),
		       PENDWR, NOPENDWR);
		FILTER(atomic_पढ़ो(&obj->n_पढ़ोs),
		       READS, NOREADS);
		FILTER(obj->events & obj->event_mask,
		       EVENTS, NOEVENTS);
		FILTER(work_busy(&obj->work), WORK, NOWORK);
	पूर्ण

	seq_म_लिखो(m,
		   "%8x %8x %s %5u %3u %3u %3u %2u %5u %2lx %2lx %2lx %1x | ",
		   obj->debug_id,
		   obj->parent ? obj->parent->debug_id : -1,
		   obj->state->लघु_name,
		   obj->n_children,
		   obj->n_ops,
		   obj->n_obj_ops,
		   obj->n_in_progress,
		   obj->n_exclusive,
		   atomic_पढ़ो(&obj->n_पढ़ोs),
		   obj->event_mask,
		   obj->events,
		   obj->flags,
		   work_busy(&obj->work));

	अगर (fscache_use_cookie(obj)) अणु
		uपूर्णांक16_t keylen = 0, auxlen = 0;

		चयन (cookie->type) अणु
		हाल 0:
			type = "IX";
			अवरोध;
		हाल 1:
			type = "DT";
			अवरोध;
		शेष:
			snम_लिखो(_type, माप(_type), "%02u",
				 cookie->type);
			type = _type;
			अवरोध;
		पूर्ण

		seq_म_लिखो(m, "%-16s %s %2lx %16p",
			   cookie->def->name,
			   type,
			   cookie->flags,
			   cookie->netfs_data);

		अगर (config & FSCACHE_OBJLIST_CONFIG_KEY)
			keylen = cookie->key_len;

		अगर (config & FSCACHE_OBJLIST_CONFIG_AUX)
			auxlen = cookie->aux_len;

		अगर (keylen > 0 || auxlen > 0) अणु
			seq_माला_दो(m, " ");
			p = keylen <= माप(cookie->अंतरभूत_key) ?
				cookie->अंतरभूत_key : cookie->key;
			क्रम (; keylen > 0; keylen--)
				seq_म_लिखो(m, "%02x", *p++);
			अगर (auxlen > 0) अणु
				अगर (config & FSCACHE_OBJLIST_CONFIG_KEY)
					seq_माला_दो(m, ", ");
				p = auxlen <= माप(cookie->अंतरभूत_aux) ?
					cookie->अंतरभूत_aux : cookie->aux;
				क्रम (; auxlen > 0; auxlen--)
					seq_म_लिखो(m, "%02x", *p++);
			पूर्ण
		पूर्ण

		seq_माला_दो(m, "\n");
		fscache_unuse_cookie(obj);
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "<no_netfs>\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fscache_objlist_ops = अणु
	.start		= fscache_objlist_start,
	.stop		= fscache_objlist_stop,
	.next		= fscache_objlist_next,
	.show		= fscache_objlist_show,
पूर्ण;

/*
 * get the configuration क्रम filtering the list
 */
अटल व्योम fscache_objlist_config(काष्ठा fscache_objlist_data *data)
अणु
#अगर_घोषित CONFIG_KEYS
	स्थिर काष्ठा user_key_payload *confkey;
	अचिन्हित दीर्घ config;
	काष्ठा key *key;
	स्थिर अक्षर *buf;
	पूर्णांक len;

	key = request_key(&key_type_user, "fscache:objlist", शून्य);
	अगर (IS_ERR(key))
		जाओ no_config;

	config = 0;
	rcu_पढ़ो_lock();

	confkey = user_key_payload_rcu(key);
	अगर (!confkey) अणु
		/* key was revoked */
		rcu_पढ़ो_unlock();
		key_put(key);
		जाओ no_config;
	पूर्ण

	buf = confkey->data;

	क्रम (len = confkey->datalen - 1; len >= 0; len--) अणु
		चयन (buf[len]) अणु
		हाल 'K': config |= FSCACHE_OBJLIST_CONFIG_KEY;		अवरोध;
		हाल 'A': config |= FSCACHE_OBJLIST_CONFIG_AUX;		अवरोध;
		हाल 'C': config |= FSCACHE_OBJLIST_CONFIG_COOKIE;	अवरोध;
		हाल 'c': config |= FSCACHE_OBJLIST_CONFIG_NOCOOKIE;	अवरोध;
		हाल 'B': config |= FSCACHE_OBJLIST_CONFIG_BUSY;	अवरोध;
		हाल 'b': config |= FSCACHE_OBJLIST_CONFIG_IDLE;	अवरोध;
		हाल 'W': config |= FSCACHE_OBJLIST_CONFIG_PENDWR;	अवरोध;
		हाल 'w': config |= FSCACHE_OBJLIST_CONFIG_NOPENDWR;	अवरोध;
		हाल 'R': config |= FSCACHE_OBJLIST_CONFIG_READS;	अवरोध;
		हाल 'r': config |= FSCACHE_OBJLIST_CONFIG_NOREADS;	अवरोध;
		हाल 'S': config |= FSCACHE_OBJLIST_CONFIG_WORK;	अवरोध;
		हाल 's': config |= FSCACHE_OBJLIST_CONFIG_NOWORK;	अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	key_put(key);

	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_COOKIE | FSCACHE_OBJLIST_CONFIG_NOCOOKIE)))
	    config   |= FSCACHE_OBJLIST_CONFIG_COOKIE | FSCACHE_OBJLIST_CONFIG_NOCOOKIE;
	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_BUSY | FSCACHE_OBJLIST_CONFIG_IDLE)))
	    config   |= FSCACHE_OBJLIST_CONFIG_BUSY | FSCACHE_OBJLIST_CONFIG_IDLE;
	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_PENDWR | FSCACHE_OBJLIST_CONFIG_NOPENDWR)))
	    config   |= FSCACHE_OBJLIST_CONFIG_PENDWR | FSCACHE_OBJLIST_CONFIG_NOPENDWR;
	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_READS | FSCACHE_OBJLIST_CONFIG_NOREADS)))
	    config   |= FSCACHE_OBJLIST_CONFIG_READS | FSCACHE_OBJLIST_CONFIG_NOREADS;
	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_EVENTS | FSCACHE_OBJLIST_CONFIG_NOEVENTS)))
	    config   |= FSCACHE_OBJLIST_CONFIG_EVENTS | FSCACHE_OBJLIST_CONFIG_NOEVENTS;
	अगर (!(config & (FSCACHE_OBJLIST_CONFIG_WORK | FSCACHE_OBJLIST_CONFIG_NOWORK)))
	    config   |= FSCACHE_OBJLIST_CONFIG_WORK | FSCACHE_OBJLIST_CONFIG_NOWORK;

	data->config = config;
	वापस;

no_config:
#पूर्ण_अगर
	data->config = अच_दीर्घ_उच्च;
पूर्ण

/*
 * खोलो "/proc/fs/fscache/objects" to provide a list of active objects
 * - can be configured by a user-defined key added to the caller's keyrings
 */
अटल पूर्णांक fscache_objlist_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fscache_objlist_data *data;

	data = __seq_खोलो_निजी(file, &fscache_objlist_ops, माप(*data));
	अगर (!data)
		वापस -ENOMEM;

	/* get the configuration key */
	fscache_objlist_config(data);

	वापस 0;
पूर्ण

/*
 * clean up on बंद
 */
अटल पूर्णांक fscache_objlist_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;

	kमुक्त(m->निजी);
	m->निजी = शून्य;
	वापस seq_release(inode, file);
पूर्ण

स्थिर काष्ठा proc_ops fscache_objlist_proc_ops = अणु
	.proc_खोलो	= fscache_objlist_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= fscache_objlist_release,
पूर्ण;
