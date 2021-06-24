<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * VIDEO MOTION CODECs पूर्णांकernal API क्रम video devices
 *
 * Interface क्रम MJPEG (and maybe later MPEG/WAVELETS) codec's
 * bound to a master device.
 *
 * (c) 2002 Wolfgang Scherr <scherr@net4you.at>
 */

#घोषणा VIDEOCODEC_VERSION "v0.2"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

// kernel config is here (procfs flag)

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#पूर्ण_अगर

#समावेश "videocodec.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-4)");

#घोषणा dprपूर्णांकk(num, क्रमmat, args...) \
	करो अणु \
		अगर (debug >= num) \
			prपूर्णांकk(क्रमmat, ##args); \
	पूर्ण जबतक (0)

काष्ठा attached_list अणु
	काष्ठा videocodec *codec;
	काष्ठा attached_list *next;
पूर्ण;

काष्ठा codec_list अणु
	स्थिर काष्ठा videocodec *codec;
	पूर्णांक attached;
	काष्ठा attached_list *list;
	काष्ठा codec_list *next;
पूर्ण;

अटल काष्ठा codec_list *codeclist_top;

/* ================================================= */
/* function prototypes of the master/slave पूर्णांकerface */
/* ================================================= */

काष्ठा videocodec *videocodec_attach(काष्ठा videocodec_master *master)
अणु
	काष्ठा codec_list *h = codeclist_top;
	काष्ठा attached_list *a, *ptr;
	काष्ठा videocodec *codec;
	पूर्णांक res;

	अगर (!master) अणु
		pr_err("%s: no data\n", __func__);
		वापस शून्य;
	पूर्ण

	dprपूर्णांकk(2, "%s: '%s', flags %lx, magic %lx\n", __func__,
		master->name, master->flags, master->magic);

	अगर (!h) अणु
		pr_err("%s: no device available\n", __func__);
		वापस शून्य;
	पूर्ण

	जबतक (h) अणु
		// attach only अगर the slave has at least the flags
		// expected by the master
		अगर ((master->flags & h->codec->flags) == master->flags) अणु
			dprपूर्णांकk(4, "%s: try '%s'\n", __func__, h->codec->name);

			अगर (!try_module_get(h->codec->owner))
				वापस शून्य;

			codec = kmemdup(h->codec, माप(काष्ठा videocodec), GFP_KERNEL);
			अगर (!codec)
				जाओ out_module_put;

			res = म_माप(codec->name);
			snम_लिखो(codec->name + res, माप(codec->name) - res, "[%d]", h->attached);
			codec->master_data = master;
			res = codec->setup(codec);
			अगर (res == 0) अणु
				dprपूर्णांकk(3, "%s: '%s'\n", __func__, codec->name);
				ptr = kzalloc(माप(*ptr), GFP_KERNEL);
				अगर (!ptr)
					जाओ out_kमुक्त;
				ptr->codec = codec;

				a = h->list;
				अगर (!a) अणु
					h->list = ptr;
					dprपूर्णांकk(4, "videocodec: first element\n");
				पूर्ण अन्यथा अणु
					जबतक (a->next)
						a = a->next;	// find end
					a->next = ptr;
					dprपूर्णांकk(4, "videocodec: in after '%s'\n", h->codec->name);
				पूर्ण

				h->attached += 1;
				वापस codec;
			पूर्ण अन्यथा अणु
				kमुक्त(codec);
			पूर्ण
		पूर्ण
		h = h->next;
	पूर्ण

	pr_err("%s: no codec found!\n", __func__);
	वापस शून्य;

 out_module_put:
	module_put(h->codec->owner);
 out_kमुक्त:
	kमुक्त(codec);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(videocodec_attach);

पूर्णांक videocodec_detach(काष्ठा videocodec *codec)
अणु
	काष्ठा codec_list *h = codeclist_top;
	काष्ठा attached_list *a, *prev;
	पूर्णांक res;

	अगर (!codec) अणु
		pr_err("%s: no data\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(2, "%s: '%s', type: %x, flags %lx, magic %lx\n", __func__,
		codec->name, codec->type, codec->flags, codec->magic);

	अगर (!h) अणु
		pr_err("%s: no device left...\n", __func__);
		वापस -ENXIO;
	पूर्ण

	जबतक (h) अणु
		a = h->list;
		prev = शून्य;
		जबतक (a) अणु
			अगर (codec == a->codec) अणु
				res = a->codec->unset(a->codec);
				अगर (res >= 0) अणु
					dprपूर्णांकk(3, "%s: '%s'\n", __func__, a->codec->name);
					a->codec->master_data = शून्य;
				पूर्ण अन्यथा अणु
					pr_err("%s: '%s'\n", __func__, a->codec->name);
					a->codec->master_data = शून्य;
				पूर्ण
				अगर (!prev) अणु
					h->list = a->next;
					dprपूर्णांकk(4, "videocodec: delete first\n");
				पूर्ण अन्यथा अणु
					prev->next = a->next;
					dprपूर्णांकk(4, "videocodec: delete middle\n");
				पूर्ण
				module_put(a->codec->owner);
				kमुक्त(a->codec);
				kमुक्त(a);
				h->attached -= 1;
				वापस 0;
			पूर्ण
			prev = a;
			a = a->next;
		पूर्ण
		h = h->next;
	पूर्ण

	pr_err("%s: given codec not found!\n", __func__);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(videocodec_detach);

पूर्णांक videocodec_रेजिस्टर(स्थिर काष्ठा videocodec *codec)
अणु
	काष्ठा codec_list *ptr, *h = codeclist_top;

	अगर (!codec) अणु
		pr_err("%s: no data!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(2,
		"videocodec: register '%s', type: %x, flags %lx, magic %lx\n",
		codec->name, codec->type, codec->flags, codec->magic);

	ptr = kzalloc(माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;
	ptr->codec = codec;

	अगर (!h) अणु
		codeclist_top = ptr;
		dprपूर्णांकk(4, "videocodec: hooked in as first element\n");
	पूर्ण अन्यथा अणु
		जबतक (h->next)
			h = h->next;	// find the end
		h->next = ptr;
		dprपूर्णांकk(4, "videocodec: hooked in after '%s'\n",
			h->codec->name);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(videocodec_रेजिस्टर);

पूर्णांक videocodec_unरेजिस्टर(स्थिर काष्ठा videocodec *codec)
अणु
	काष्ठा codec_list *prev = शून्य, *h = codeclist_top;

	अगर (!codec) अणु
		pr_err("%s: no data!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(2,
		"videocodec: unregister '%s', type: %x, flags %lx, magic %lx\n",
		codec->name, codec->type, codec->flags, codec->magic);

	अगर (!h) अणु
		pr_err("%s: no device left...\n", __func__);
		वापस -ENXIO;
	पूर्ण

	जबतक (h) अणु
		अगर (codec == h->codec) अणु
			अगर (h->attached) अणु
				pr_err("videocodec: '%s' is used\n", h->codec->name);
				वापस -EBUSY;
			पूर्ण
			dprपूर्णांकk(3, "videocodec: unregister '%s' is ok.\n",
				h->codec->name);
			अगर (!prev) अणु
				codeclist_top = h->next;
				dprपूर्णांकk(4,
					"videocodec: delete first element\n");
			पूर्ण अन्यथा अणु
				prev->next = h->next;
				dprपूर्णांकk(4,
					"videocodec: delete middle element\n");
			पूर्ण
			kमुक्त(h);
			वापस 0;
		पूर्ण
		prev = h;
		h = h->next;
	पूर्ण

	pr_err("%s: given codec not found!\n", __func__);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(videocodec_unरेजिस्टर);

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_videocodecs_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा codec_list *h = codeclist_top;
	काष्ठा attached_list *a;

	seq_म_लिखो(m, "<S>lave or attached <M>aster name  type flags    magic    ");
	seq_म_लिखो(m, "(connected as)\n");

	जबतक (h) अणु
		seq_म_लिखो(m, "S %32s %04x %08lx %08lx (TEMPLATE)\n",
			   h->codec->name, h->codec->type,
			      h->codec->flags, h->codec->magic);
		a = h->list;
		जबतक (a) अणु
			seq_म_लिखो(m, "M %32s %04x %08lx %08lx (%s)\n",
				   a->codec->master_data->name,
				      a->codec->master_data->type,
				      a->codec->master_data->flags,
				      a->codec->master_data->magic,
				      a->codec->name);
			a = a->next;
		पूर्ण
		h = h->next;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ===================== */
/* hook in driver module */
/* ===================== */
अटल पूर्णांक __init videocodec_init(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अटल काष्ठा proc_dir_entry *videocodec_proc_entry;
#पूर्ण_अगर

	pr_info("Linux video codec intermediate layer: %s\n", VIDEOCODEC_VERSION);

#अगर_घोषित CONFIG_PROC_FS
	videocodec_proc_entry = proc_create_single("videocodecs", 0, शून्य, proc_videocodecs_show);
	अगर (!videocodec_proc_entry)
		pr_err("videocodec: can't init procfs.\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास videocodec_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("videocodecs", शून्य);
#पूर्ण_अगर
पूर्ण

module_init(videocodec_init);
module_निकास(videocodec_निकास);

MODULE_AUTHOR("Wolfgang Scherr <scherr@net4you.at>");
MODULE_DESCRIPTION("Intermediate API module for video codecs "
		   VIDEOCODEC_VERSION);
MODULE_LICENSE("GPL");
