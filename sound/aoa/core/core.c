<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio driver core
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश "../aoa.h"
#समावेश "alsa.h"

MODULE_DESCRIPTION("Apple Onboard Audio Sound Driver");
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");

/* We allow only one fabric. This simplअगरies things,
 * and more करोn't really make that much sense */
अटल काष्ठा aoa_fabric *fabric;
अटल LIST_HEAD(codec_list);

अटल पूर्णांक attach_codec_to_fabric(काष्ठा aoa_codec *c)
अणु
	पूर्णांक err;

	अगर (!try_module_get(c->owner))
		वापस -EBUSY;
	/* found_codec has to be asचिन्हित */
	err = -ENOENT;
	अगर (fabric->found_codec)
		err = fabric->found_codec(c);
	अगर (err) अणु
		module_put(c->owner);
		prपूर्णांकk(KERN_ERR "snd-aoa: fabric didn't like codec %s\n",
				c->name);
		वापस err;
	पूर्ण
	c->fabric = fabric;

	err = 0;
	अगर (c->init)
		err = c->init(c);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa: codec %s didn't init\n", c->name);
		c->fabric = शून्य;
		अगर (fabric->हटाओ_codec)
			fabric->हटाओ_codec(c);
		module_put(c->owner);
		वापस err;
	पूर्ण
	अगर (fabric->attached_codec)
		fabric->attached_codec(c);
	वापस 0;
पूर्ण

पूर्णांक aoa_codec_रेजिस्टर(काष्ठा aoa_codec *codec)
अणु
	पूर्णांक err = 0;

	/* अगर there's a fabric alपढ़ोy, we can tell अगर we
	 * will want to have this codec, so propagate error
	 * through. Otherwise, this will happen later... */
	अगर (fabric)
		err = attach_codec_to_fabric(codec);
	अगर (!err)
		list_add(&codec->list, &codec_list);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_codec_रेजिस्टर);

व्योम aoa_codec_unरेजिस्टर(काष्ठा aoa_codec *codec)
अणु
	list_del(&codec->list);
	अगर (codec->fabric && codec->निकास)
		codec->निकास(codec);
	अगर (fabric && fabric->हटाओ_codec)
		fabric->हटाओ_codec(codec);
	codec->fabric = शून्य;
	module_put(codec->owner);
पूर्ण
EXPORT_SYMBOL_GPL(aoa_codec_unरेजिस्टर);

पूर्णांक aoa_fabric_रेजिस्टर(काष्ठा aoa_fabric *new_fabric, काष्ठा device *dev)
अणु
	काष्ठा aoa_codec *c;
	पूर्णांक err;

	/* allow querying क्रम presence of fabric
	 * (i.e. करो this test first!) */
	अगर (new_fabric == fabric) अणु
		err = -EALREADY;
		जाओ attach;
	पूर्ण
	अगर (fabric)
		वापस -EEXIST;
	अगर (!new_fabric)
		वापस -EINVAL;

	err = aoa_alsa_init(new_fabric->name, new_fabric->owner, dev);
	अगर (err)
		वापस err;

	fabric = new_fabric;

 attach:
	list_क्रम_each_entry(c, &codec_list, list) अणु
		अगर (c->fabric != fabric)
			attach_codec_to_fabric(c);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_fabric_रेजिस्टर);

व्योम aoa_fabric_unरेजिस्टर(काष्ठा aoa_fabric *old_fabric)
अणु
	काष्ठा aoa_codec *c;

	अगर (fabric != old_fabric)
		वापस;

	list_क्रम_each_entry(c, &codec_list, list) अणु
		अगर (c->fabric)
			aoa_fabric_unlink_codec(c);
	पूर्ण

	aoa_alsa_cleanup();

	fabric = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_fabric_unरेजिस्टर);

व्योम aoa_fabric_unlink_codec(काष्ठा aoa_codec *codec)
अणु
	अगर (!codec->fabric) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa: fabric unassigned "
				"in aoa_fabric_unlink_codec\n");
		dump_stack();
		वापस;
	पूर्ण
	अगर (codec->निकास)
		codec->निकास(codec);
	अगर (codec->fabric->हटाओ_codec)
		codec->fabric->हटाओ_codec(codec);
	codec->fabric = शून्य;
	module_put(codec->owner);
पूर्ण
EXPORT_SYMBOL_GPL(aoa_fabric_unlink_codec);

अटल पूर्णांक __init aoa_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास aoa_निकास(व्योम)
अणु
	aoa_alsa_cleanup();
पूर्ण

module_init(aoa_init);
module_निकास(aoa_निकास);
