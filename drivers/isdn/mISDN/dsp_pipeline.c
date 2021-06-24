<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dsp_pipeline.c: pipelined audio processing
 *
 * Copyright (C) 2007, Nadi Sarrar
 *
 * Nadi Sarrar <nadi@beronet.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mISDNdsp.h>
#समावेश <linux/export.h>
#समावेश "dsp.h"
#समावेश "dsp_hwec.h"

/* uncomment क्रम debugging */
/*#घोषणा PIPELINE_DEBUG*/

काष्ठा dsp_pipeline_entry अणु
	काष्ठा mISDN_dsp_element *elem;
	व्योम                *p;
	काष्ठा list_head     list;
पूर्ण;
काष्ठा dsp_element_entry अणु
	काष्ठा mISDN_dsp_element *elem;
	काष्ठा device	     dev;
	काष्ठा list_head     list;
पूर्ण;

अटल LIST_HEAD(dsp_elements);

/* sysfs */
अटल काष्ठा class *elements_class;

अटल sमाप_प्रकार
attr_show_args(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDN_dsp_element *elem = dev_get_drvdata(dev);
	पूर्णांक i;
	अक्षर *p = buf;

	*buf = 0;
	क्रम (i = 0; i < elem->num_args; i++)
		p += प्र_लिखो(p, "Name:        %s\n%s%s%sDescription: %s\n\n",
			     elem->args[i].name,
			     elem->args[i].def ? "Default:     " : "",
			     elem->args[i].def ? elem->args[i].def : "",
			     elem->args[i].def ? "\n" : "",
			     elem->args[i].desc);

	वापस p - buf;
पूर्ण

अटल काष्ठा device_attribute element_attributes[] = अणु
	__ATTR(args, 0444, attr_show_args, शून्य),
पूर्ण;

अटल व्योम
mISDN_dsp_dev_release(काष्ठा device *dev)
अणु
	काष्ठा dsp_element_entry *entry =
		container_of(dev, काष्ठा dsp_element_entry, dev);
	list_del(&entry->list);
	kमुक्त(entry);
पूर्ण

पूर्णांक mISDN_dsp_element_रेजिस्टर(काष्ठा mISDN_dsp_element *elem)
अणु
	काष्ठा dsp_element_entry *entry;
	पूर्णांक ret, i;

	अगर (!elem)
		वापस -EINVAL;

	entry = kzalloc(माप(काष्ठा dsp_element_entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	entry->elem = elem;

	entry->dev.class = elements_class;
	entry->dev.release = mISDN_dsp_dev_release;
	dev_set_drvdata(&entry->dev, elem);
	dev_set_name(&entry->dev, "%s", elem->name);
	ret = device_रेजिस्टर(&entry->dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register %s\n",
		       __func__, elem->name);
		जाओ err1;
	पूर्ण
	list_add_tail(&entry->list, &dsp_elements);

	क्रम (i = 0; i < ARRAY_SIZE(element_attributes); ++i) अणु
		ret = device_create_file(&entry->dev,
					 &element_attributes[i]);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to create device file\n",
			       __func__);
			जाओ err2;
		पूर्ण
	पूर्ण

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: %s registered\n", __func__, elem->name);
#पूर्ण_अगर

	वापस 0;

err2:
	device_unरेजिस्टर(&entry->dev);
	वापस ret;
err1:
	kमुक्त(entry);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mISDN_dsp_element_रेजिस्टर);

व्योम mISDN_dsp_element_unरेजिस्टर(काष्ठा mISDN_dsp_element *elem)
अणु
	काष्ठा dsp_element_entry *entry, *n;

	अगर (!elem)
		वापस;

	list_क्रम_each_entry_safe(entry, n, &dsp_elements, list)
		अगर (entry->elem == elem) अणु
			device_unरेजिस्टर(&entry->dev);
#अगर_घोषित PIPELINE_DEBUG
			prपूर्णांकk(KERN_DEBUG "%s: %s unregistered\n",
			       __func__, elem->name);
#पूर्ण_अगर
			वापस;
		पूर्ण
	prपूर्णांकk(KERN_ERR "%s: element %s not in list.\n", __func__, elem->name);
पूर्ण
EXPORT_SYMBOL(mISDN_dsp_element_unरेजिस्टर);

पूर्णांक dsp_pipeline_module_init(व्योम)
अणु
	elements_class = class_create(THIS_MODULE, "dsp_pipeline");
	अगर (IS_ERR(elements_class))
		वापस PTR_ERR(elements_class);

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: dsp pipeline module initialized\n", __func__);
#पूर्ण_अगर

	dsp_hwec_init();

	वापस 0;
पूर्ण

व्योम dsp_pipeline_module_निकास(व्योम)
अणु
	काष्ठा dsp_element_entry *entry, *n;

	dsp_hwec_निकास();

	class_destroy(elements_class);

	list_क्रम_each_entry_safe(entry, n, &dsp_elements, list) अणु
		list_del(&entry->list);
		prपूर्णांकk(KERN_WARNING "%s: element was still registered: %s\n",
		       __func__, entry->elem->name);
		kमुक्त(entry);
	पूर्ण

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: dsp pipeline module exited\n", __func__);
#पूर्ण_अगर
पूर्ण

पूर्णांक dsp_pipeline_init(काष्ठा dsp_pipeline *pipeline)
अणु
	अगर (!pipeline)
		वापस -EINVAL;

	INIT_LIST_HEAD(&pipeline->list);

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: dsp pipeline ready\n", __func__);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम _dsp_pipeline_destroy(काष्ठा dsp_pipeline *pipeline)
अणु
	काष्ठा dsp_pipeline_entry *entry, *n;

	list_क्रम_each_entry_safe(entry, n, &pipeline->list, list) अणु
		list_del(&entry->list);
		अगर (entry->elem == dsp_hwec)
			dsp_hwec_disable(container_of(pipeline, काष्ठा dsp,
						      pipeline));
		अन्यथा
			entry->elem->मुक्त(entry->p);
		kमुक्त(entry);
	पूर्ण
पूर्ण

व्योम dsp_pipeline_destroy(काष्ठा dsp_pipeline *pipeline)
अणु

	अगर (!pipeline)
		वापस;

	_dsp_pipeline_destroy(pipeline);

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: dsp pipeline destroyed\n", __func__);
#पूर्ण_अगर
पूर्ण

पूर्णांक dsp_pipeline_build(काष्ठा dsp_pipeline *pipeline, स्थिर अक्षर *cfg)
अणु
	पूर्णांक incomplete = 0, found = 0;
	अक्षर *dup, *tok, *name, *args;
	काष्ठा dsp_element_entry *entry, *n;
	काष्ठा dsp_pipeline_entry *pipeline_entry;
	काष्ठा mISDN_dsp_element *elem;

	अगर (!pipeline)
		वापस -EINVAL;

	अगर (!list_empty(&pipeline->list))
		_dsp_pipeline_destroy(pipeline);

	dup = kstrdup(cfg, GFP_ATOMIC);
	अगर (!dup)
		वापस 0;
	जबतक ((tok = strsep(&dup, "|"))) अणु
		अगर (!म_माप(tok))
			जारी;
		name = strsep(&tok, "(");
		args = strsep(&tok, ")");
		अगर (args && !*args)
			args = शून्य;

		list_क्रम_each_entry_safe(entry, n, &dsp_elements, list)
			अगर (!म_भेद(entry->elem->name, name)) अणु
				elem = entry->elem;

				pipeline_entry = kदो_स्मृति(माप(काष्ठा
								dsp_pipeline_entry), GFP_ATOMIC);
				अगर (!pipeline_entry) अणु
					prपूर्णांकk(KERN_ERR "%s: failed to add "
					       "entry to pipeline: %s (out of "
					       "memory)\n", __func__, elem->name);
					incomplete = 1;
					जाओ _out;
				पूर्ण
				pipeline_entry->elem = elem;

				अगर (elem == dsp_hwec) अणु
					/* This is a hack to make the hwec
					   available as a pipeline module */
					dsp_hwec_enable(container_of(pipeline,
								     काष्ठा dsp, pipeline), args);
					list_add_tail(&pipeline_entry->list,
						      &pipeline->list);
				पूर्ण अन्यथा अणु
					pipeline_entry->p = elem->new(args);
					अगर (pipeline_entry->p) अणु
						list_add_tail(&pipeline_entry->
							      list, &pipeline->list);
#अगर_घोषित PIPELINE_DEBUG
						prपूर्णांकk(KERN_DEBUG "%s: created "
						       "instance of %s%s%s\n",
						       __func__, name, args ?
						       " with args " : "", args ?
						       args : "");
#पूर्ण_अगर
					पूर्ण अन्यथा अणु
						prपूर्णांकk(KERN_ERR "%s: failed "
						       "to add entry to pipeline: "
						       "%s (new() returned NULL)\n",
						       __func__, elem->name);
						kमुक्त(pipeline_entry);
						incomplete = 1;
					पूर्ण
				पूर्ण
				found = 1;
				अवरोध;
			पूर्ण

		अगर (found)
			found = 0;
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: element not found, skipping: "
			       "%s\n", __func__, name);
			incomplete = 1;
		पूर्ण
	पूर्ण

_out:
	अगर (!list_empty(&pipeline->list))
		pipeline->inuse = 1;
	अन्यथा
		pipeline->inuse = 0;

#अगर_घोषित PIPELINE_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: dsp pipeline built%s: %s\n",
	       __func__, incomplete ? " incomplete" : "", cfg);
#पूर्ण_अगर
	kमुक्त(dup);
	वापस 0;
पूर्ण

व्योम dsp_pipeline_process_tx(काष्ठा dsp_pipeline *pipeline, u8 *data, पूर्णांक len)
अणु
	काष्ठा dsp_pipeline_entry *entry;

	अगर (!pipeline)
		वापस;

	list_क्रम_each_entry(entry, &pipeline->list, list)
		अगर (entry->elem->process_tx)
			entry->elem->process_tx(entry->p, data, len);
पूर्ण

व्योम dsp_pipeline_process_rx(काष्ठा dsp_pipeline *pipeline, u8 *data, पूर्णांक len,
			     अचिन्हित पूर्णांक txlen)
अणु
	काष्ठा dsp_pipeline_entry *entry;

	अगर (!pipeline)
		वापस;

	list_क्रम_each_entry_reverse(entry, &pipeline->list, list)
		अगर (entry->elem->process_rx)
			entry->elem->process_rx(entry->p, data, len, txlen);
पूर्ण
