<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uvc_configfs.c
 *
 * Configfs support क्रम the uvc function.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#समावेश <linux/sort.h>

#समावेश "u_uvc.h"
#समावेश "uvc_configfs.h"

/* -----------------------------------------------------------------------------
 * Global Utility Structures and Macros
 */

#घोषणा UVCG_STREAMING_CONTROL_SIZE	1

#घोषणा UVC_ATTR(prefix, cname, aname) \
अटल काष्ठा configfs_attribute prefix##attr_##cname = अणु \
	.ca_name	= __stringअगरy(aname),				\
	.ca_mode	= S_IRUGO | S_IWUGO,				\
	.ca_owner	= THIS_MODULE,					\
	.show		= prefix##cname##_show,				\
	.store		= prefix##cname##_store,			\
पूर्ण

#घोषणा UVC_ATTR_RO(prefix, cname, aname) \
अटल काष्ठा configfs_attribute prefix##attr_##cname = अणु \
	.ca_name	= __stringअगरy(aname),				\
	.ca_mode	= S_IRUGO,					\
	.ca_owner	= THIS_MODULE,					\
	.show		= prefix##cname##_show,				\
पूर्ण

#घोषणा le8_to_cpu(x)	(x)
#घोषणा cpu_to_le8(x)	(x)

अटल पूर्णांक uvcg_config_compare_u32(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	u32 li = *(स्थिर u32 *)l;
	u32 ri = *(स्थिर u32 *)r;

	वापस li < ri ? -1 : li == ri ? 0 : 1;
पूर्ण

अटल अंतरभूत काष्ठा f_uvc_opts *to_f_uvc_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_uvc_opts,
			    func_inst.group);
पूर्ण

काष्ठा uvcg_config_group_type अणु
	काष्ठा config_item_type type;
	स्थिर अक्षर *name;
	स्थिर काष्ठा uvcg_config_group_type **children;
	पूर्णांक (*create_children)(काष्ठा config_group *group);
पूर्ण;

अटल व्योम uvcg_config_item_release(काष्ठा config_item *item)
अणु
	काष्ठा config_group *group = to_config_group(item);

	kमुक्त(group);
पूर्ण

अटल काष्ठा configfs_item_operations uvcg_config_item_ops = अणु
	.release	= uvcg_config_item_release,
पूर्ण;

अटल पूर्णांक uvcg_config_create_group(काष्ठा config_group *parent,
				    स्थिर काष्ठा uvcg_config_group_type *type);

अटल पूर्णांक uvcg_config_create_children(काष्ठा config_group *group,
				स्थिर काष्ठा uvcg_config_group_type *type)
अणु
	स्थिर काष्ठा uvcg_config_group_type **child;
	पूर्णांक ret;

	अगर (type->create_children)
		वापस type->create_children(group);

	क्रम (child = type->children; child && *child; ++child) अणु
		ret = uvcg_config_create_group(group, *child);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvcg_config_create_group(काष्ठा config_group *parent,
				    स्थिर काष्ठा uvcg_config_group_type *type)
अणु
	काष्ठा config_group *group;

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस -ENOMEM;

	config_group_init_type_name(group, type->name, &type->type);
	configfs_add_शेष_group(group, parent);

	वापस uvcg_config_create_children(group, type);
पूर्ण

अटल व्योम uvcg_config_हटाओ_children(काष्ठा config_group *group)
अणु
	काष्ठा config_group *child, *n;

	list_क्रम_each_entry_safe(child, n, &group->शेष_groups, group_entry) अणु
		list_del(&child->group_entry);
		uvcg_config_हटाओ_children(child);
		config_item_put(&child->cg_item);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * control/header/<NAME>
 * control/header
 */

DECLARE_UVC_HEADER_DESCRIPTOR(1);

काष्ठा uvcg_control_header अणु
	काष्ठा config_item		item;
	काष्ठा UVC_HEADER_DESCRIPTOR(1)	desc;
	अचिन्हित			linked;
पूर्ण;

अटल काष्ठा uvcg_control_header *to_uvcg_control_header(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा uvcg_control_header, item);
पूर्ण

#घोषणा UVCG_CTRL_HDR_ATTR(cname, aname, bits, limit)			\
अटल sमाप_प्रकार uvcg_control_header_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा uvcg_control_header *ch = to_uvcg_control_header(item);	\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &ch->item.ci_group->cg_subsys->su_mutex;\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = ch->item.ci_parent->ci_parent->ci_parent;		\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(ch->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार								\
uvcg_control_header_##cname##_store(काष्ठा config_item *item,		\
			   स्थिर अक्षर *page, माप_प्रकार len)		\
अणु									\
	काष्ठा uvcg_control_header *ch = to_uvcg_control_header(item);	\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &ch->item.ci_group->cg_subsys->su_mutex;\
	पूर्णांक ret;							\
	u##bits num;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = ch->item.ci_parent->ci_parent->ci_parent;		\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	अगर (ch->linked || opts->refcnt) अणु				\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou##bits(page, 0, &num);				\
	अगर (ret)							\
		जाओ end;						\
									\
	अगर (num > limit) अणु						\
		ret = -EINVAL;						\
		जाओ end;						\
	पूर्ण								\
	ch->desc.aname = cpu_to_le##bits(num);				\
	ret = len;							\
end:									\
	mutex_unlock(&opts->lock);					\
	mutex_unlock(su_mutex);						\
	वापस ret;							\
पूर्ण									\
									\
UVC_ATTR(uvcg_control_header_, cname, aname)

UVCG_CTRL_HDR_ATTR(bcd_uvc, bcdUVC, 16, 0xffff);

UVCG_CTRL_HDR_ATTR(dw_घड़ी_frequency, dwClockFrequency, 32, 0x7fffffff);

#अघोषित UVCG_CTRL_HDR_ATTR

अटल काष्ठा configfs_attribute *uvcg_control_header_attrs[] = अणु
	&uvcg_control_header_attr_bcd_uvc,
	&uvcg_control_header_attr_dw_घड़ी_frequency,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_control_header_type = अणु
	.ct_item_ops	= &uvcg_config_item_ops,
	.ct_attrs	= uvcg_control_header_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_item *uvcg_control_header_make(काष्ठा config_group *group,
						    स्थिर अक्षर *name)
अणु
	काष्ठा uvcg_control_header *h;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	h->desc.bLength			= UVC_DT_HEADER_SIZE(1);
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VC_HEADER;
	h->desc.bcdUVC			= cpu_to_le16(0x0110);
	h->desc.dwClockFrequency	= cpu_to_le32(48000000);

	config_item_init_type_name(&h->item, name, &uvcg_control_header_type);

	वापस &h->item;
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_control_header_grp_ops = अणु
	.make_item		= uvcg_control_header_make,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_control_header_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_group_ops	= &uvcg_control_header_grp_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "header",
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/processing/शेष
 */

#घोषणा UVCG_DEFAULT_PROCESSING_ATTR(cname, aname, bits)		\
अटल sमाप_प्रकार uvcg_शेष_processing_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;		\
	काष्ठा uvc_processing_unit_descriptor *pd;			\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;	\
	opts = to_f_uvc_opts(opts_item);				\
	pd = &opts->uvc_processing;					\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(pd->aname));	\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_शेष_processing_, cname, aname)

UVCG_DEFAULT_PROCESSING_ATTR(b_unit_id, bUnitID, 8);
UVCG_DEFAULT_PROCESSING_ATTR(b_source_id, bSourceID, 8);
UVCG_DEFAULT_PROCESSING_ATTR(w_max_multiplier, wMaxMultiplier, 16);
UVCG_DEFAULT_PROCESSING_ATTR(i_processing, iProcessing, 8);

#अघोषित UVCG_DEFAULT_PROCESSING_ATTR

अटल sमाप_प्रकार uvcg_शेष_processing_bm_controls_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा config_group *group = to_config_group(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;
	काष्ठा uvc_processing_unit_descriptor *pd;
	पूर्णांक result, i;
	अक्षर *pg = page;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);
	pd = &opts->uvc_processing;

	mutex_lock(&opts->lock);
	क्रम (result = 0, i = 0; i < pd->bControlSize; ++i) अणु
		result += प्र_लिखो(pg, "%u\n", pd->bmControls[i]);
		pg = page + result;
	पूर्ण
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);

	वापस result;
पूर्ण

UVC_ATTR_RO(uvcg_शेष_processing_, bm_controls, bmControls);

अटल काष्ठा configfs_attribute *uvcg_शेष_processing_attrs[] = अणु
	&uvcg_शेष_processing_attr_b_unit_id,
	&uvcg_शेष_processing_attr_b_source_id,
	&uvcg_शेष_processing_attr_w_max_multiplier,
	&uvcg_शेष_processing_attr_bm_controls,
	&uvcg_शेष_processing_attr_i_processing,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_शेष_processing_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_processing_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "default",
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/processing
 */

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_processing_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "processing",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_शेष_processing_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/terminal/camera/शेष
 */

#घोषणा UVCG_DEFAULT_CAMERA_ATTR(cname, aname, bits)			\
अटल sमाप_प्रकार uvcg_शेष_camera_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;		\
	काष्ठा uvc_camera_terminal_descriptor *cd;			\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent->	\
			ci_parent;					\
	opts = to_f_uvc_opts(opts_item);				\
	cd = &opts->uvc_camera_terminal;				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(cd->aname));	\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
									\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_शेष_camera_, cname, aname)

UVCG_DEFAULT_CAMERA_ATTR(b_terminal_id, bTerminalID, 8);
UVCG_DEFAULT_CAMERA_ATTR(w_terminal_type, wTerminalType, 16);
UVCG_DEFAULT_CAMERA_ATTR(b_assoc_terminal, bAssocTerminal, 8);
UVCG_DEFAULT_CAMERA_ATTR(i_terminal, iTerminal, 8);
UVCG_DEFAULT_CAMERA_ATTR(w_objective_focal_length_min, wObjectiveFocalLengthMin,
			 16);
UVCG_DEFAULT_CAMERA_ATTR(w_objective_focal_length_max, wObjectiveFocalLengthMax,
			 16);
UVCG_DEFAULT_CAMERA_ATTR(w_ocular_focal_length, wOcularFocalLength,
			 16);

#अघोषित UVCG_DEFAULT_CAMERA_ATTR

अटल sमाप_प्रकार uvcg_शेष_camera_bm_controls_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा config_group *group = to_config_group(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;
	काष्ठा uvc_camera_terminal_descriptor *cd;
	पूर्णांक result, i;
	अक्षर *pg = page;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent->
			ci_parent;
	opts = to_f_uvc_opts(opts_item);
	cd = &opts->uvc_camera_terminal;

	mutex_lock(&opts->lock);
	क्रम (result = 0, i = 0; i < cd->bControlSize; ++i) अणु
		result += प्र_लिखो(pg, "%u\n", cd->bmControls[i]);
		pg = page + result;
	पूर्ण
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);
	वापस result;
पूर्ण

UVC_ATTR_RO(uvcg_शेष_camera_, bm_controls, bmControls);

अटल काष्ठा configfs_attribute *uvcg_शेष_camera_attrs[] = अणु
	&uvcg_शेष_camera_attr_b_terminal_id,
	&uvcg_शेष_camera_attr_w_terminal_type,
	&uvcg_शेष_camera_attr_b_assoc_terminal,
	&uvcg_शेष_camera_attr_i_terminal,
	&uvcg_शेष_camera_attr_w_objective_focal_length_min,
	&uvcg_शेष_camera_attr_w_objective_focal_length_max,
	&uvcg_शेष_camera_attr_w_ocular_focal_length,
	&uvcg_शेष_camera_attr_bm_controls,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_शेष_camera_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_camera_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "default",
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/terminal/camera
 */

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_camera_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "camera",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_शेष_camera_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/terminal/output/शेष
 */

#घोषणा UVCG_DEFAULT_OUTPUT_ATTR(cname, aname, bits)			\
अटल sमाप_प्रकार uvcg_शेष_output_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;		\
	काष्ठा uvc_output_terminal_descriptor *cd;			\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = group->cg_item.ci_parent->ci_parent->		\
			ci_parent->ci_parent;				\
	opts = to_f_uvc_opts(opts_item);				\
	cd = &opts->uvc_output_terminal;				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(cd->aname));	\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
									\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_शेष_output_, cname, aname)

UVCG_DEFAULT_OUTPUT_ATTR(b_terminal_id, bTerminalID, 8);
UVCG_DEFAULT_OUTPUT_ATTR(w_terminal_type, wTerminalType, 16);
UVCG_DEFAULT_OUTPUT_ATTR(b_assoc_terminal, bAssocTerminal, 8);
UVCG_DEFAULT_OUTPUT_ATTR(b_source_id, bSourceID, 8);
UVCG_DEFAULT_OUTPUT_ATTR(i_terminal, iTerminal, 8);

#अघोषित UVCG_DEFAULT_OUTPUT_ATTR

अटल काष्ठा configfs_attribute *uvcg_शेष_output_attrs[] = अणु
	&uvcg_शेष_output_attr_b_terminal_id,
	&uvcg_शेष_output_attr_w_terminal_type,
	&uvcg_शेष_output_attr_b_assoc_terminal,
	&uvcg_शेष_output_attr_b_source_id,
	&uvcg_शेष_output_attr_i_terminal,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_शेष_output_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_output_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "default",
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/terminal/output
 */

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_output_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "output",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_शेष_output_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/terminal
 */

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_terminal_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "terminal",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_camera_grp_type,
		&uvcg_output_grp_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/class/अणुfs|ssपूर्ण
 */

काष्ठा uvcg_control_class_group अणु
	काष्ठा config_group group;
	स्थिर अक्षर *name;
पूर्ण;

अटल अंतरभूत काष्ठा uvc_descriptor_header
**uvcg_get_ctl_class_arr(काष्ठा config_item *i, काष्ठा f_uvc_opts *o)
अणु
	काष्ठा uvcg_control_class_group *group =
		container_of(i, काष्ठा uvcg_control_class_group,
			     group.cg_item);

	अगर (!म_भेद(group->name, "fs"))
		वापस o->uvc_fs_control_cls;

	अगर (!म_भेद(group->name, "ss"))
		वापस o->uvc_ss_control_cls;

	वापस शून्य;
पूर्ण

अटल पूर्णांक uvcg_control_class_allow_link(काष्ठा config_item *src,
					 काष्ठा config_item *target)
अणु
	काष्ठा config_item *control, *header;
	काष्ठा f_uvc_opts *opts;
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा uvc_descriptor_header **class_array;
	काष्ठा uvcg_control_header *target_hdr;
	पूर्णांक ret = -EINVAL;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	control = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(control), "header");
	अगर (!header || target->ci_parent != header)
		जाओ out;

	opts = to_f_uvc_opts(control->ci_parent);

	mutex_lock(&opts->lock);

	class_array = uvcg_get_ctl_class_arr(src, opts);
	अगर (!class_array)
		जाओ unlock;
	अगर (opts->refcnt || class_array[0]) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	target_hdr = to_uvcg_control_header(target);
	++target_hdr->linked;
	class_array[0] = (काष्ठा uvc_descriptor_header *)&target_hdr->desc;
	ret = 0;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

अटल व्योम uvcg_control_class_drop_link(काष्ठा config_item *src,
					काष्ठा config_item *target)
अणु
	काष्ठा config_item *control, *header;
	काष्ठा f_uvc_opts *opts;
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा uvc_descriptor_header **class_array;
	काष्ठा uvcg_control_header *target_hdr;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	control = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(control), "header");
	अगर (!header || target->ci_parent != header)
		जाओ out;

	opts = to_f_uvc_opts(control->ci_parent);

	mutex_lock(&opts->lock);

	class_array = uvcg_get_ctl_class_arr(src, opts);
	अगर (!class_array || opts->refcnt)
		जाओ unlock;

	target_hdr = to_uvcg_control_header(target);
	--target_hdr->linked;
	class_array[0] = शून्य;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
पूर्ण

अटल काष्ठा configfs_item_operations uvcg_control_class_item_ops = अणु
	.release	= uvcg_config_item_release,
	.allow_link	= uvcg_control_class_allow_link,
	.drop_link	= uvcg_control_class_drop_link,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_control_class_type = अणु
	.ct_item_ops	= &uvcg_control_class_item_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control/class
 */

अटल पूर्णांक uvcg_control_class_create_children(काष्ठा config_group *parent)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु "fs", "ss" पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(names); ++i) अणु
		काष्ठा uvcg_control_class_group *group;

		group = kzalloc(माप(*group), GFP_KERNEL);
		अगर (!group)
			वापस -ENOMEM;

		group->name = names[i];

		config_group_init_type_name(&group->group, group->name,
					    &uvcg_control_class_type);
		configfs_add_शेष_group(&group->group, parent);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_control_class_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "class",
	.create_children = uvcg_control_class_create_children,
पूर्ण;

/* -----------------------------------------------------------------------------
 * control
 */

अटल sमाप_प्रकार uvcg_शेष_control_b_पूर्णांकerface_number_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा config_group *group = to_config_group(item);
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;
	काष्ठा config_item *opts_item;
	काष्ठा f_uvc_opts *opts;
	पूर्णांक result = 0;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = item->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result += प्र_लिखो(page, "%u\n", opts->control_पूर्णांकerface);
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);

	वापस result;
पूर्ण

UVC_ATTR_RO(uvcg_शेष_control_, b_पूर्णांकerface_number, bInterfaceNumber);

अटल काष्ठा configfs_attribute *uvcg_शेष_control_attrs[] = अणु
	&uvcg_शेष_control_attr_b_पूर्णांकerface_number,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_control_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_control_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "control",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_control_header_grp_type,
		&uvcg_processing_grp_type,
		&uvcg_terminal_grp_type,
		&uvcg_control_class_grp_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/uncompressed
 * streaming/mjpeg
 */

अटल स्थिर अक्षर * स्थिर uvcg_क्रमmat_names[] = अणु
	"uncompressed",
	"mjpeg",
पूर्ण;

क्रमागत uvcg_क्रमmat_type अणु
	UVCG_UNCOMPRESSED = 0,
	UVCG_MJPEG,
पूर्ण;

काष्ठा uvcg_क्रमmat अणु
	काष्ठा config_group	group;
	क्रमागत uvcg_क्रमmat_type	type;
	अचिन्हित		linked;
	अचिन्हित		num_frames;
	__u8			bmaControls[UVCG_STREAMING_CONTROL_SIZE];
पूर्ण;

अटल काष्ठा uvcg_क्रमmat *to_uvcg_क्रमmat(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा uvcg_क्रमmat, group);
पूर्ण

अटल sमाप_प्रकार uvcg_क्रमmat_bma_controls_show(काष्ठा uvcg_क्रमmat *f, अक्षर *page)
अणु
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &f->group.cg_subsys->su_mutex;
	पूर्णांक result, i;
	अक्षर *pg = page;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = f->group.cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result = प्र_लिखो(pg, "0x");
	pg += result;
	क्रम (i = 0; i < UVCG_STREAMING_CONTROL_SIZE; ++i) अणु
		result += प्र_लिखो(pg, "%x\n", f->bmaControls[i]);
		pg = page + result;
	पूर्ण
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);
	वापस result;
पूर्ण

अटल sमाप_प्रकार uvcg_क्रमmat_bma_controls_store(काष्ठा uvcg_क्रमmat *ch,
					      स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &ch->group.cg_subsys->su_mutex;
	पूर्णांक ret = -EINVAL;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = ch->group.cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	अगर (ch->linked || opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	अगर (len < 4 || *page != '0' ||
	    (*(page + 1) != 'x' && *(page + 1) != 'X'))
		जाओ end;
	ret = hex2bin(ch->bmaControls, page + 2, 1);
	अगर (ret < 0)
		जाओ end;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

काष्ठा uvcg_क्रमmat_ptr अणु
	काष्ठा uvcg_क्रमmat	*fmt;
	काष्ठा list_head	entry;
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/header/<NAME>
 * streaming/header
 */

काष्ठा uvcg_streaming_header अणु
	काष्ठा config_item				item;
	काष्ठा uvc_input_header_descriptor		desc;
	अचिन्हित					linked;
	काष्ठा list_head				क्रमmats;
	अचिन्हित					num_fmt;
पूर्ण;

अटल काष्ठा uvcg_streaming_header *to_uvcg_streaming_header(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा uvcg_streaming_header, item);
पूर्ण

अटल व्योम uvcg_क्रमmat_set_indices(काष्ठा config_group *fmt);

अटल पूर्णांक uvcg_streaming_header_allow_link(काष्ठा config_item *src,
					    काष्ठा config_item *target)
अणु
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा config_item *opts_item;
	काष्ठा f_uvc_opts *opts;
	काष्ठा uvcg_streaming_header *src_hdr;
	काष्ठा uvcg_क्रमmat *target_fmt = शून्य;
	काष्ठा uvcg_क्रमmat_ptr *क्रमmat_ptr;
	पूर्णांक i, ret = -EINVAL;

	src_hdr = to_uvcg_streaming_header(src);
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = src->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);

	अगर (src_hdr->linked) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * Linking is only allowed to direct children of the क्रमmat nodes
	 * (streaming/uncompressed or streaming/mjpeg nodes). First check that
	 * the gअक्रम-parent of the target matches the gअक्रम-parent of the source
	 * (the streaming node), and then verअगरy that the target parent is a
	 * क्रमmat node.
	 */
	अगर (src->ci_parent->ci_parent != target->ci_parent->ci_parent)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(uvcg_क्रमmat_names); ++i) अणु
		अगर (!म_भेद(target->ci_parent->ci_name, uvcg_क्रमmat_names[i]))
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(uvcg_क्रमmat_names))
		जाओ out;

	target_fmt = container_of(to_config_group(target), काष्ठा uvcg_क्रमmat,
				  group);
	अगर (!target_fmt)
		जाओ out;

	uvcg_क्रमmat_set_indices(to_config_group(target));

	क्रमmat_ptr = kzalloc(माप(*क्रमmat_ptr), GFP_KERNEL);
	अगर (!क्रमmat_ptr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = 0;
	क्रमmat_ptr->fmt = target_fmt;
	list_add_tail(&क्रमmat_ptr->entry, &src_hdr->क्रमmats);
	++src_hdr->num_fmt;
	++target_fmt->linked;

out:
	mutex_unlock(&opts->lock);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

अटल व्योम uvcg_streaming_header_drop_link(काष्ठा config_item *src,
					   काष्ठा config_item *target)
अणु
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा config_item *opts_item;
	काष्ठा f_uvc_opts *opts;
	काष्ठा uvcg_streaming_header *src_hdr;
	काष्ठा uvcg_क्रमmat *target_fmt = शून्य;
	काष्ठा uvcg_क्रमmat_ptr *क्रमmat_ptr, *पंचांगp;

	src_hdr = to_uvcg_streaming_header(src);
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = src->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	target_fmt = container_of(to_config_group(target), काष्ठा uvcg_क्रमmat,
				  group);
	अगर (!target_fmt)
		जाओ out;

	list_क्रम_each_entry_safe(क्रमmat_ptr, पंचांगp, &src_hdr->क्रमmats, entry)
		अगर (क्रमmat_ptr->fmt == target_fmt) अणु
			list_del(&क्रमmat_ptr->entry);
			kमुक्त(क्रमmat_ptr);
			--src_hdr->num_fmt;
			अवरोध;
		पूर्ण

	--target_fmt->linked;

out:
	mutex_unlock(&opts->lock);
	mutex_unlock(su_mutex);
पूर्ण

अटल काष्ठा configfs_item_operations uvcg_streaming_header_item_ops = अणु
	.release	= uvcg_config_item_release,
	.allow_link	= uvcg_streaming_header_allow_link,
	.drop_link	= uvcg_streaming_header_drop_link,
पूर्ण;

#घोषणा UVCG_STREAMING_HEADER_ATTR(cname, aname, bits)			\
अटल sमाप_प्रकार uvcg_streaming_header_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा uvcg_streaming_header *sh = to_uvcg_streaming_header(item); \
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &sh->item.ci_group->cg_subsys->su_mutex;\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = sh->item.ci_parent->ci_parent->ci_parent;		\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(sh->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_streaming_header_, cname, aname)

UVCG_STREAMING_HEADER_ATTR(bm_info, bmInfo, 8);
UVCG_STREAMING_HEADER_ATTR(b_terminal_link, bTerminalLink, 8);
UVCG_STREAMING_HEADER_ATTR(b_still_capture_method, bStillCaptureMethod, 8);
UVCG_STREAMING_HEADER_ATTR(b_trigger_support, bTriggerSupport, 8);
UVCG_STREAMING_HEADER_ATTR(b_trigger_usage, bTriggerUsage, 8);

#अघोषित UVCG_STREAMING_HEADER_ATTR

अटल काष्ठा configfs_attribute *uvcg_streaming_header_attrs[] = अणु
	&uvcg_streaming_header_attr_bm_info,
	&uvcg_streaming_header_attr_b_terminal_link,
	&uvcg_streaming_header_attr_b_still_capture_method,
	&uvcg_streaming_header_attr_b_trigger_support,
	&uvcg_streaming_header_attr_b_trigger_usage,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_streaming_header_type = अणु
	.ct_item_ops	= &uvcg_streaming_header_item_ops,
	.ct_attrs	= uvcg_streaming_header_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_item
*uvcg_streaming_header_make(काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	काष्ठा uvcg_streaming_header *h;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&h->क्रमmats);
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VS_INPUT_HEADER;
	h->desc.bTerminalLink		= 3;
	h->desc.bControlSize		= UVCG_STREAMING_CONTROL_SIZE;

	config_item_init_type_name(&h->item, name, &uvcg_streaming_header_type);

	वापस &h->item;
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_streaming_header_grp_ops = अणु
	.make_item		= uvcg_streaming_header_make,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_streaming_header_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_group_ops	= &uvcg_streaming_header_grp_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "header",
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/<mode>/<क्रमmat>/<NAME>
 */

काष्ठा uvcg_frame अणु
	काष्ठा config_item	item;
	क्रमागत uvcg_क्रमmat_type	fmt_type;
	काष्ठा अणु
		u8	b_length;
		u8	b_descriptor_type;
		u8	b_descriptor_subtype;
		u8	b_frame_index;
		u8	bm_capabilities;
		u16	w_width;
		u16	w_height;
		u32	dw_min_bit_rate;
		u32	dw_max_bit_rate;
		u32	dw_max_video_frame_buffer_size;
		u32	dw_शेष_frame_पूर्णांकerval;
		u8	b_frame_पूर्णांकerval_type;
	पूर्ण __attribute__((packed)) frame;
	u32 *dw_frame_पूर्णांकerval;
पूर्ण;

अटल काष्ठा uvcg_frame *to_uvcg_frame(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा uvcg_frame, item);
पूर्ण

#घोषणा UVCG_FRAME_ATTR(cname, aname, bits) \
अटल sमाप_प्रकार uvcg_frame_##cname##_show(काष्ठा config_item *item, अक्षर *page)\
अणु									\
	काष्ठा uvcg_frame *f = to_uvcg_frame(item);			\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &f->item.ci_group->cg_subsys->su_mutex;\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = f->item.ci_parent->ci_parent->ci_parent->ci_parent;	\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", f->frame.cname);			\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार  uvcg_frame_##cname##_store(काष्ठा config_item *item,	\
					   स्थिर अक्षर *page, माप_प्रकार len)\
अणु									\
	काष्ठा uvcg_frame *f = to_uvcg_frame(item);			\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा uvcg_क्रमmat *fmt;					\
	काष्ठा mutex *su_mutex = &f->item.ci_group->cg_subsys->su_mutex;\
	typeof(f->frame.cname) num;					\
	पूर्णांक ret;							\
									\
	ret = kstrtou##bits(page, 0, &num);				\
	अगर (ret)							\
		वापस ret;						\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = f->item.ci_parent->ci_parent->ci_parent->ci_parent;	\
	opts = to_f_uvc_opts(opts_item);				\
	fmt = to_uvcg_क्रमmat(f->item.ci_parent);			\
									\
	mutex_lock(&opts->lock);					\
	अगर (fmt->linked || opts->refcnt) अणु				\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	f->frame.cname = num;						\
	ret = len;							\
end:									\
	mutex_unlock(&opts->lock);					\
	mutex_unlock(su_mutex);						\
	वापस ret;							\
पूर्ण									\
									\
UVC_ATTR(uvcg_frame_, cname, aname);

अटल sमाप_प्रकार uvcg_frame_b_frame_index_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	काष्ठा uvcg_frame *f = to_uvcg_frame(item);
	काष्ठा uvcg_क्रमmat *fmt;
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा config_item *fmt_item;
	काष्ठा mutex *su_mutex = &f->item.ci_group->cg_subsys->su_mutex;
	पूर्णांक result;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	fmt_item = f->item.ci_parent;
	fmt = to_uvcg_क्रमmat(fmt_item);

	अगर (!fmt->linked) अणु
		result = -EBUSY;
		जाओ out;
	पूर्ण

	opts_item = fmt_item->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", f->frame.b_frame_index);
	mutex_unlock(&opts->lock);

out:
	mutex_unlock(su_mutex);
	वापस result;
पूर्ण

UVC_ATTR_RO(uvcg_frame_, b_frame_index, bFrameIndex);

UVCG_FRAME_ATTR(bm_capabilities, bmCapabilities, 8);
UVCG_FRAME_ATTR(w_width, wWidth, 16);
UVCG_FRAME_ATTR(w_height, wHeight, 16);
UVCG_FRAME_ATTR(dw_min_bit_rate, dwMinBitRate, 32);
UVCG_FRAME_ATTR(dw_max_bit_rate, dwMaxBitRate, 32);
UVCG_FRAME_ATTR(dw_max_video_frame_buffer_size, dwMaxVideoFrameBufferSize, 32);
UVCG_FRAME_ATTR(dw_शेष_frame_पूर्णांकerval, dwDefaultFrameInterval, 32);

#अघोषित UVCG_FRAME_ATTR

अटल sमाप_प्रकार uvcg_frame_dw_frame_पूर्णांकerval_show(काष्ठा config_item *item,
						 अक्षर *page)
अणु
	काष्ठा uvcg_frame *frm = to_uvcg_frame(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &frm->item.ci_group->cg_subsys->su_mutex;
	पूर्णांक result, i;
	अक्षर *pg = page;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = frm->item.ci_parent->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	क्रम (result = 0, i = 0; i < frm->frame.b_frame_पूर्णांकerval_type; ++i) अणु
		result += प्र_लिखो(pg, "%u\n", frm->dw_frame_पूर्णांकerval[i]);
		pg = page + result;
	पूर्ण
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);
	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक __uvcg_count_frm_पूर्णांकrv(अक्षर *buf, व्योम *priv)
अणु
	++*((पूर्णांक *)priv);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __uvcg_fill_frm_पूर्णांकrv(अक्षर *buf, व्योम *priv)
अणु
	u32 num, **पूर्णांकerv;
	पूर्णांक ret;

	ret = kstrtou32(buf, 0, &num);
	अगर (ret)
		वापस ret;

	पूर्णांकerv = priv;
	**पूर्णांकerv = num;
	++*पूर्णांकerv;

	वापस 0;
पूर्ण

अटल पूर्णांक __uvcg_iter_frm_पूर्णांकrv(स्थिर अक्षर *page, माप_प्रकार len,
				 पूर्णांक (*fun)(अक्षर *, व्योम *), व्योम *priv)
अणु
	/* sign, base 2 representation, newline, terminator */
	अक्षर buf[1 + माप(u32) * 8 + 1 + 1];
	स्थिर अक्षर *pg = page;
	पूर्णांक i, ret;

	अगर (!fun)
		वापस -EINVAL;

	जबतक (pg - page < len) अणु
		i = 0;
		जबतक (i < माप(buf) && (pg - page < len) &&
				*pg != '\0' && *pg != '\n')
			buf[i++] = *pg++;
		अगर (i == माप(buf))
			वापस -EINVAL;
		जबतक ((pg - page < len) && (*pg == '\0' || *pg == '\n'))
			++pg;
		buf[i] = '\0';
		ret = fun(buf, priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार uvcg_frame_dw_frame_पूर्णांकerval_store(काष्ठा config_item *item,
						  स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा uvcg_frame *ch = to_uvcg_frame(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा uvcg_क्रमmat *fmt;
	काष्ठा mutex *su_mutex = &ch->item.ci_group->cg_subsys->su_mutex;
	पूर्णांक ret = 0, n = 0;
	u32 *frm_पूर्णांकrv, *पंचांगp;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = ch->item.ci_parent->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);
	fmt = to_uvcg_क्रमmat(ch->item.ci_parent);

	mutex_lock(&opts->lock);
	अगर (fmt->linked || opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = __uvcg_iter_frm_पूर्णांकrv(page, len, __uvcg_count_frm_पूर्णांकrv, &n);
	अगर (ret)
		जाओ end;

	पंचांगp = frm_पूर्णांकrv = kसुस्मृति(n, माप(u32), GFP_KERNEL);
	अगर (!frm_पूर्णांकrv) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	ret = __uvcg_iter_frm_पूर्णांकrv(page, len, __uvcg_fill_frm_पूर्णांकrv, &पंचांगp);
	अगर (ret) अणु
		kमुक्त(frm_पूर्णांकrv);
		जाओ end;
	पूर्ण

	kमुक्त(ch->dw_frame_पूर्णांकerval);
	ch->dw_frame_पूर्णांकerval = frm_पूर्णांकrv;
	ch->frame.b_frame_पूर्णांकerval_type = n;
	sort(ch->dw_frame_पूर्णांकerval, n, माप(*ch->dw_frame_पूर्णांकerval),
	     uvcg_config_compare_u32, शून्य);
	ret = len;

end:
	mutex_unlock(&opts->lock);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

UVC_ATTR(uvcg_frame_, dw_frame_पूर्णांकerval, dwFrameInterval);

अटल काष्ठा configfs_attribute *uvcg_frame_attrs[] = अणु
	&uvcg_frame_attr_b_frame_index,
	&uvcg_frame_attr_bm_capabilities,
	&uvcg_frame_attr_w_width,
	&uvcg_frame_attr_w_height,
	&uvcg_frame_attr_dw_min_bit_rate,
	&uvcg_frame_attr_dw_max_bit_rate,
	&uvcg_frame_attr_dw_max_video_frame_buffer_size,
	&uvcg_frame_attr_dw_शेष_frame_पूर्णांकerval,
	&uvcg_frame_attr_dw_frame_पूर्णांकerval,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_frame_type = अणु
	.ct_item_ops	= &uvcg_config_item_ops,
	.ct_attrs	= uvcg_frame_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_item *uvcg_frame_make(काष्ठा config_group *group,
					   स्थिर अक्षर *name)
अणु
	काष्ठा uvcg_frame *h;
	काष्ठा uvcg_क्रमmat *fmt;
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	h->frame.b_descriptor_type		= USB_DT_CS_INTERFACE;
	h->frame.b_frame_index			= 1;
	h->frame.w_width			= 640;
	h->frame.w_height			= 360;
	h->frame.dw_min_bit_rate		= 18432000;
	h->frame.dw_max_bit_rate		= 55296000;
	h->frame.dw_max_video_frame_buffer_size	= 460800;
	h->frame.dw_शेष_frame_पूर्णांकerval	= 666666;

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	fmt = to_uvcg_क्रमmat(&group->cg_item);
	अगर (fmt->type == UVCG_UNCOMPRESSED) अणु
		h->frame.b_descriptor_subtype = UVC_VS_FRAME_UNCOMPRESSED;
		h->fmt_type = UVCG_UNCOMPRESSED;
	पूर्ण अन्यथा अगर (fmt->type == UVCG_MJPEG) अणु
		h->frame.b_descriptor_subtype = UVC_VS_FRAME_MJPEG;
		h->fmt_type = UVCG_MJPEG;
	पूर्ण अन्यथा अणु
		mutex_unlock(&opts->lock);
		kमुक्त(h);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	++fmt->num_frames;
	mutex_unlock(&opts->lock);

	config_item_init_type_name(&h->item, name, &uvcg_frame_type);

	वापस &h->item;
पूर्ण

अटल व्योम uvcg_frame_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	काष्ठा uvcg_क्रमmat *fmt;
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	fmt = to_uvcg_क्रमmat(&group->cg_item);
	--fmt->num_frames;
	mutex_unlock(&opts->lock);

	config_item_put(item);
पूर्ण

अटल व्योम uvcg_क्रमmat_set_indices(काष्ठा config_group *fmt)
अणु
	काष्ठा config_item *ci;
	अचिन्हित पूर्णांक i = 1;

	list_क्रम_each_entry(ci, &fmt->cg_children, ci_entry) अणु
		काष्ठा uvcg_frame *frm;

		अगर (ci->ci_type != &uvcg_frame_type)
			जारी;

		frm = to_uvcg_frame(ci);
		frm->frame.b_frame_index = i++;
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * streaming/uncompressed/<NAME>
 */

काष्ठा uvcg_uncompressed अणु
	काष्ठा uvcg_क्रमmat		fmt;
	काष्ठा uvc_क्रमmat_uncompressed	desc;
पूर्ण;

अटल काष्ठा uvcg_uncompressed *to_uvcg_uncompressed(काष्ठा config_item *item)
अणु
	वापस container_of(
		container_of(to_config_group(item), काष्ठा uvcg_क्रमmat, group),
		काष्ठा uvcg_uncompressed, fmt);
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_uncompressed_group_ops = अणु
	.make_item		= uvcg_frame_make,
	.drop_item		= uvcg_frame_drop,
पूर्ण;

अटल sमाप_प्रकार uvcg_uncompressed_guid_क्रमmat_show(काष्ठा config_item *item,
							अक्षर *page)
अणु
	काष्ठा uvcg_uncompressed *ch = to_uvcg_uncompressed(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &ch->fmt.group.cg_subsys->su_mutex;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = ch->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	स_नकल(page, ch->desc.guidFormat, माप(ch->desc.guidFormat));
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);

	वापस माप(ch->desc.guidFormat);
पूर्ण

अटल sमाप_प्रकार uvcg_uncompressed_guid_क्रमmat_store(काष्ठा config_item *item,
						   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा uvcg_uncompressed *ch = to_uvcg_uncompressed(item);
	काष्ठा f_uvc_opts *opts;
	काष्ठा config_item *opts_item;
	काष्ठा mutex *su_mutex = &ch->fmt.group.cg_subsys->su_mutex;
	पूर्णांक ret;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = ch->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	अगर (ch->fmt.linked || opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	स_नकल(ch->desc.guidFormat, page,
	       min(माप(ch->desc.guidFormat), len));
	ret = माप(ch->desc.guidFormat);

end:
	mutex_unlock(&opts->lock);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

UVC_ATTR(uvcg_uncompressed_, guid_क्रमmat, guidFormat);

#घोषणा UVCG_UNCOMPRESSED_ATTR_RO(cname, aname, bits)			\
अटल sमाप_प्रकार uvcg_uncompressed_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा uvcg_uncompressed *u = to_uvcg_uncompressed(item);	\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(u->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_uncompressed_, cname, aname);

#घोषणा UVCG_UNCOMPRESSED_ATTR(cname, aname, bits)			\
अटल sमाप_प्रकार uvcg_uncompressed_##cname##_show(			\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा uvcg_uncompressed *u = to_uvcg_uncompressed(item);	\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(u->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार								\
uvcg_uncompressed_##cname##_store(काष्ठा config_item *item,		\
				    स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा uvcg_uncompressed *u = to_uvcg_uncompressed(item);	\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक ret;							\
	u8 num;								\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	अगर (u->fmt.linked || opts->refcnt) अणु				\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou8(page, 0, &num);					\
	अगर (ret)							\
		जाओ end;						\
									\
	u->desc.aname = num;						\
	ret = len;							\
end:									\
	mutex_unlock(&opts->lock);					\
	mutex_unlock(su_mutex);						\
	वापस ret;							\
पूर्ण									\
									\
UVC_ATTR(uvcg_uncompressed_, cname, aname);

UVCG_UNCOMPRESSED_ATTR_RO(b_क्रमmat_index, bFormatIndex, 8);
UVCG_UNCOMPRESSED_ATTR(b_bits_per_pixel, bBitsPerPixel, 8);
UVCG_UNCOMPRESSED_ATTR(b_शेष_frame_index, bDefaultFrameIndex, 8);
UVCG_UNCOMPRESSED_ATTR_RO(b_aspect_ratio_x, bAspectRatioX, 8);
UVCG_UNCOMPRESSED_ATTR_RO(b_aspect_ratio_y, bAspectRatioY, 8);
UVCG_UNCOMPRESSED_ATTR_RO(bm_पूर्णांकerface_flags, bmInterfaceFlags, 8);

#अघोषित UVCG_UNCOMPRESSED_ATTR
#अघोषित UVCG_UNCOMPRESSED_ATTR_RO

अटल अंतरभूत sमाप_प्रकार
uvcg_uncompressed_bma_controls_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा uvcg_uncompressed *unc = to_uvcg_uncompressed(item);
	वापस uvcg_क्रमmat_bma_controls_show(&unc->fmt, page);
पूर्ण

अटल अंतरभूत sमाप_प्रकार
uvcg_uncompressed_bma_controls_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा uvcg_uncompressed *unc = to_uvcg_uncompressed(item);
	वापस uvcg_क्रमmat_bma_controls_store(&unc->fmt, page, len);
पूर्ण

UVC_ATTR(uvcg_uncompressed_, bma_controls, bmaControls);

अटल काष्ठा configfs_attribute *uvcg_uncompressed_attrs[] = अणु
	&uvcg_uncompressed_attr_b_क्रमmat_index,
	&uvcg_uncompressed_attr_guid_क्रमmat,
	&uvcg_uncompressed_attr_b_bits_per_pixel,
	&uvcg_uncompressed_attr_b_शेष_frame_index,
	&uvcg_uncompressed_attr_b_aspect_ratio_x,
	&uvcg_uncompressed_attr_b_aspect_ratio_y,
	&uvcg_uncompressed_attr_bm_पूर्णांकerface_flags,
	&uvcg_uncompressed_attr_bma_controls,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_uncompressed_type = अणु
	.ct_item_ops	= &uvcg_config_item_ops,
	.ct_group_ops	= &uvcg_uncompressed_group_ops,
	.ct_attrs	= uvcg_uncompressed_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *uvcg_uncompressed_make(काष्ठा config_group *group,
						   स्थिर अक्षर *name)
अणु
	अटल अक्षर guid[] = अणु
		'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00,
		 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71
	पूर्ण;
	काष्ठा uvcg_uncompressed *h;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	h->desc.bLength			= UVC_DT_FORMAT_UNCOMPRESSED_SIZE;
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VS_FORMAT_UNCOMPRESSED;
	स_नकल(h->desc.guidFormat, guid, माप(guid));
	h->desc.bBitsPerPixel		= 16;
	h->desc.bDefaultFrameIndex	= 1;
	h->desc.bAspectRatioX		= 0;
	h->desc.bAspectRatioY		= 0;
	h->desc.bmInterfaceFlags	= 0;
	h->desc.bCopyProtect		= 0;

	h->fmt.type = UVCG_UNCOMPRESSED;
	config_group_init_type_name(&h->fmt.group, name,
				    &uvcg_uncompressed_type);

	वापस &h->fmt.group;
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_uncompressed_grp_ops = अणु
	.make_group		= uvcg_uncompressed_make,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_uncompressed_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_group_ops	= &uvcg_uncompressed_grp_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "uncompressed",
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/mjpeg/<NAME>
 */

काष्ठा uvcg_mjpeg अणु
	काष्ठा uvcg_क्रमmat		fmt;
	काष्ठा uvc_क्रमmat_mjpeg		desc;
पूर्ण;

अटल काष्ठा uvcg_mjpeg *to_uvcg_mjpeg(काष्ठा config_item *item)
अणु
	वापस container_of(
		container_of(to_config_group(item), काष्ठा uvcg_क्रमmat, group),
		काष्ठा uvcg_mjpeg, fmt);
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_mjpeg_group_ops = अणु
	.make_item		= uvcg_frame_make,
	.drop_item		= uvcg_frame_drop,
पूर्ण;

#घोषणा UVCG_MJPEG_ATTR_RO(cname, aname, bits)				\
अटल sमाप_प्रकार uvcg_mjpeg_##cname##_show(काष्ठा config_item *item, अक्षर *page)\
अणु									\
	काष्ठा uvcg_mjpeg *u = to_uvcg_mjpeg(item);			\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(u->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_mjpeg_, cname, aname)

#घोषणा UVCG_MJPEG_ATTR(cname, aname, bits)				\
अटल sमाप_प्रकार uvcg_mjpeg_##cname##_show(काष्ठा config_item *item, अक्षर *page)\
अणु									\
	काष्ठा uvcg_mjpeg *u = to_uvcg_mjpeg(item);			\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(u->desc.aname));\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार								\
uvcg_mjpeg_##cname##_store(काष्ठा config_item *item,			\
			   स्थिर अक्षर *page, माप_प्रकार len)		\
अणु									\
	काष्ठा uvcg_mjpeg *u = to_uvcg_mjpeg(item);			\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &u->fmt.group.cg_subsys->su_mutex;	\
	पूर्णांक ret;							\
	u8 num;								\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = u->fmt.group.cg_item.ci_parent->ci_parent->ci_parent;\
	opts = to_f_uvc_opts(opts_item);				\
									\
	mutex_lock(&opts->lock);					\
	अगर (u->fmt.linked || opts->refcnt) अणु				\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou8(page, 0, &num);					\
	अगर (ret)							\
		जाओ end;						\
									\
	u->desc.aname = num;						\
	ret = len;							\
end:									\
	mutex_unlock(&opts->lock);					\
	mutex_unlock(su_mutex);						\
	वापस ret;							\
पूर्ण									\
									\
UVC_ATTR(uvcg_mjpeg_, cname, aname)

UVCG_MJPEG_ATTR_RO(b_क्रमmat_index, bFormatIndex, 8);
UVCG_MJPEG_ATTR(b_शेष_frame_index, bDefaultFrameIndex, 8);
UVCG_MJPEG_ATTR_RO(bm_flags, bmFlags, 8);
UVCG_MJPEG_ATTR_RO(b_aspect_ratio_x, bAspectRatioX, 8);
UVCG_MJPEG_ATTR_RO(b_aspect_ratio_y, bAspectRatioY, 8);
UVCG_MJPEG_ATTR_RO(bm_पूर्णांकerface_flags, bmInterfaceFlags, 8);

#अघोषित UVCG_MJPEG_ATTR
#अघोषित UVCG_MJPEG_ATTR_RO

अटल अंतरभूत sमाप_प्रकार
uvcg_mjpeg_bma_controls_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा uvcg_mjpeg *u = to_uvcg_mjpeg(item);
	वापस uvcg_क्रमmat_bma_controls_show(&u->fmt, page);
पूर्ण

अटल अंतरभूत sमाप_प्रकार
uvcg_mjpeg_bma_controls_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा uvcg_mjpeg *u = to_uvcg_mjpeg(item);
	वापस uvcg_क्रमmat_bma_controls_store(&u->fmt, page, len);
पूर्ण

UVC_ATTR(uvcg_mjpeg_, bma_controls, bmaControls);

अटल काष्ठा configfs_attribute *uvcg_mjpeg_attrs[] = अणु
	&uvcg_mjpeg_attr_b_क्रमmat_index,
	&uvcg_mjpeg_attr_b_शेष_frame_index,
	&uvcg_mjpeg_attr_bm_flags,
	&uvcg_mjpeg_attr_b_aspect_ratio_x,
	&uvcg_mjpeg_attr_b_aspect_ratio_y,
	&uvcg_mjpeg_attr_bm_पूर्णांकerface_flags,
	&uvcg_mjpeg_attr_bma_controls,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_mjpeg_type = अणु
	.ct_item_ops	= &uvcg_config_item_ops,
	.ct_group_ops	= &uvcg_mjpeg_group_ops,
	.ct_attrs	= uvcg_mjpeg_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *uvcg_mjpeg_make(काष्ठा config_group *group,
						   स्थिर अक्षर *name)
अणु
	काष्ठा uvcg_mjpeg *h;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	h->desc.bLength			= UVC_DT_FORMAT_MJPEG_SIZE;
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VS_FORMAT_MJPEG;
	h->desc.bDefaultFrameIndex	= 1;
	h->desc.bAspectRatioX		= 0;
	h->desc.bAspectRatioY		= 0;
	h->desc.bmInterfaceFlags	= 0;
	h->desc.bCopyProtect		= 0;

	h->fmt.type = UVCG_MJPEG;
	config_group_init_type_name(&h->fmt.group, name,
				    &uvcg_mjpeg_type);

	वापस &h->fmt.group;
पूर्ण

अटल काष्ठा configfs_group_operations uvcg_mjpeg_grp_ops = अणु
	.make_group		= uvcg_mjpeg_make,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_mjpeg_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_group_ops	= &uvcg_mjpeg_grp_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "mjpeg",
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/color_matching/शेष
 */

#घोषणा UVCG_DEFAULT_COLOR_MATCHING_ATTR(cname, aname, bits)		\
अटल sमाप_प्रकार uvcg_शेष_color_matching_##cname##_show(		\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा config_group *group = to_config_group(item);		\
	काष्ठा f_uvc_opts *opts;					\
	काष्ठा config_item *opts_item;					\
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;		\
	काष्ठा uvc_color_matching_descriptor *cd;			\
	पूर्णांक result;							\
									\
	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */	\
									\
	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;	\
	opts = to_f_uvc_opts(opts_item);				\
	cd = &opts->uvc_color_matching;					\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", le##bits##_to_cpu(cd->aname));	\
	mutex_unlock(&opts->lock);					\
									\
	mutex_unlock(su_mutex);						\
	वापस result;							\
पूर्ण									\
									\
UVC_ATTR_RO(uvcg_शेष_color_matching_, cname, aname)

UVCG_DEFAULT_COLOR_MATCHING_ATTR(b_color_primaries, bColorPrimaries, 8);
UVCG_DEFAULT_COLOR_MATCHING_ATTR(b_transfer_अक्षरacteristics,
				 bTransferCharacteristics, 8);
UVCG_DEFAULT_COLOR_MATCHING_ATTR(b_matrix_coefficients, bMatrixCoefficients, 8);

#अघोषित UVCG_DEFAULT_COLOR_MATCHING_ATTR

अटल काष्ठा configfs_attribute *uvcg_शेष_color_matching_attrs[] = अणु
	&uvcg_शेष_color_matching_attr_b_color_primaries,
	&uvcg_शेष_color_matching_attr_b_transfer_अक्षरacteristics,
	&uvcg_शेष_color_matching_attr_b_matrix_coefficients,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_शेष_color_matching_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_color_matching_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "default",
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/color_matching
 */

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_color_matching_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "color_matching",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_शेष_color_matching_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/class/अणुfs|hs|ssपूर्ण
 */

काष्ठा uvcg_streaming_class_group अणु
	काष्ठा config_group group;
	स्थिर अक्षर *name;
पूर्ण;

अटल अंतरभूत काष्ठा uvc_descriptor_header
***__uvcg_get_stream_class_arr(काष्ठा config_item *i, काष्ठा f_uvc_opts *o)
अणु
	काष्ठा uvcg_streaming_class_group *group =
		container_of(i, काष्ठा uvcg_streaming_class_group,
			     group.cg_item);

	अगर (!म_भेद(group->name, "fs"))
		वापस &o->uvc_fs_streaming_cls;

	अगर (!म_भेद(group->name, "hs"))
		वापस &o->uvc_hs_streaming_cls;

	अगर (!म_भेद(group->name, "ss"))
		वापस &o->uvc_ss_streaming_cls;

	वापस शून्य;
पूर्ण

क्रमागत uvcg_strm_type अणु
	UVCG_HEADER = 0,
	UVCG_FORMAT,
	UVCG_FRAME
पूर्ण;

/*
 * Iterate over a hierarchy of streaming descriptors' config items.
 * The items are created by the user with configfs.
 *
 * It "processes" the header poपूर्णांकed to by @priv1, then क्रम each क्रमmat
 * that follows the header "processes" the क्रमmat itself and then क्रम
 * each frame inside a क्रमmat "processes" the frame.
 *
 * As a "processing" function the @fun is used.
 *
 * __uvcg_iter_strm_cls() is used in two context: first, to calculate
 * the amount of memory needed क्रम an array of streaming descriptors
 * and second, to actually fill the array.
 *
 * @h: streaming header poपूर्णांकer
 * @priv2: an "inout" parameter (the caller might want to see the changes to it)
 * @priv3: an "inout" parameter (the caller might want to see the changes to it)
 * @fun: callback function क्रम processing each level of the hierarchy
 */
अटल पूर्णांक __uvcg_iter_strm_cls(काष्ठा uvcg_streaming_header *h,
	व्योम *priv2, व्योम *priv3,
	पूर्णांक (*fun)(व्योम *, व्योम *, व्योम *, पूर्णांक, क्रमागत uvcg_strm_type type))
अणु
	काष्ठा uvcg_क्रमmat_ptr *f;
	काष्ठा config_group *grp;
	काष्ठा config_item *item;
	काष्ठा uvcg_frame *frm;
	पूर्णांक ret, i, j;

	अगर (!fun)
		वापस -EINVAL;

	i = j = 0;
	ret = fun(h, priv2, priv3, 0, UVCG_HEADER);
	अगर (ret)
		वापस ret;
	list_क्रम_each_entry(f, &h->क्रमmats, entry) अणु
		ret = fun(f->fmt, priv2, priv3, i++, UVCG_FORMAT);
		अगर (ret)
			वापस ret;
		grp = &f->fmt->group;
		list_क्रम_each_entry(item, &grp->cg_children, ci_entry) अणु
			frm = to_uvcg_frame(item);
			ret = fun(frm, priv2, priv3, j++, UVCG_FRAME);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Count how many bytes are needed क्रम an array of streaming descriptors.
 *
 * @priv1: poपूर्णांकer to a header, क्रमmat or frame
 * @priv2: inout parameter, accumulated size of the array
 * @priv3: inout parameter, accumulated number of the array elements
 * @n: unused, this function's prototype must match @fun in __uvcg_iter_strm_cls
 */
अटल पूर्णांक __uvcg_cnt_strm(व्योम *priv1, व्योम *priv2, व्योम *priv3, पूर्णांक n,
			   क्रमागत uvcg_strm_type type)
अणु
	माप_प्रकार *size = priv2;
	माप_प्रकार *count = priv3;

	चयन (type) अणु
	हाल UVCG_HEADER: अणु
		काष्ठा uvcg_streaming_header *h = priv1;

		*size += माप(h->desc);
		/* bmaControls */
		*size += h->num_fmt * UVCG_STREAMING_CONTROL_SIZE;
	पूर्ण
	अवरोध;
	हाल UVCG_FORMAT: अणु
		काष्ठा uvcg_क्रमmat *fmt = priv1;

		अगर (fmt->type == UVCG_UNCOMPRESSED) अणु
			काष्ठा uvcg_uncompressed *u =
				container_of(fmt, काष्ठा uvcg_uncompressed,
					     fmt);

			*size += माप(u->desc);
		पूर्ण अन्यथा अगर (fmt->type == UVCG_MJPEG) अणु
			काष्ठा uvcg_mjpeg *m =
				container_of(fmt, काष्ठा uvcg_mjpeg, fmt);

			*size += माप(m->desc);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अवरोध;
	हाल UVCG_FRAME: अणु
		काष्ठा uvcg_frame *frm = priv1;
		पूर्णांक sz = माप(frm->dw_frame_पूर्णांकerval);

		*size += माप(frm->frame);
		*size += frm->frame.b_frame_पूर्णांकerval_type * sz;
	पूर्ण
	अवरोध;
	पूर्ण

	++*count;

	वापस 0;
पूर्ण

/*
 * Fill an array of streaming descriptors.
 *
 * @priv1: poपूर्णांकer to a header, क्रमmat or frame
 * @priv2: inout parameter, poपूर्णांकer पूर्णांकo a block of memory
 * @priv3: inout parameter, poपूर्णांकer to a 2-dimensional array
 */
अटल पूर्णांक __uvcg_fill_strm(व्योम *priv1, व्योम *priv2, व्योम *priv3, पूर्णांक n,
			    क्रमागत uvcg_strm_type type)
अणु
	व्योम **dest = priv2;
	काष्ठा uvc_descriptor_header ***array = priv3;
	माप_प्रकार sz;

	**array = *dest;
	++*array;

	चयन (type) अणु
	हाल UVCG_HEADER: अणु
		काष्ठा uvc_input_header_descriptor *ihdr = *dest;
		काष्ठा uvcg_streaming_header *h = priv1;
		काष्ठा uvcg_क्रमmat_ptr *f;

		स_नकल(*dest, &h->desc, माप(h->desc));
		*dest += माप(h->desc);
		sz = UVCG_STREAMING_CONTROL_SIZE;
		list_क्रम_each_entry(f, &h->क्रमmats, entry) अणु
			स_नकल(*dest, f->fmt->bmaControls, sz);
			*dest += sz;
		पूर्ण
		ihdr->bLength = माप(h->desc) + h->num_fmt * sz;
		ihdr->bNumFormats = h->num_fmt;
	पूर्ण
	अवरोध;
	हाल UVCG_FORMAT: अणु
		काष्ठा uvcg_क्रमmat *fmt = priv1;

		अगर (fmt->type == UVCG_UNCOMPRESSED) अणु
			काष्ठा uvcg_uncompressed *u =
				container_of(fmt, काष्ठा uvcg_uncompressed,
					     fmt);

			u->desc.bFormatIndex = n + 1;
			u->desc.bNumFrameDescriptors = fmt->num_frames;
			स_नकल(*dest, &u->desc, माप(u->desc));
			*dest += माप(u->desc);
		पूर्ण अन्यथा अगर (fmt->type == UVCG_MJPEG) अणु
			काष्ठा uvcg_mjpeg *m =
				container_of(fmt, काष्ठा uvcg_mjpeg, fmt);

			m->desc.bFormatIndex = n + 1;
			m->desc.bNumFrameDescriptors = fmt->num_frames;
			स_नकल(*dest, &m->desc, माप(m->desc));
			*dest += माप(m->desc);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अवरोध;
	हाल UVCG_FRAME: अणु
		काष्ठा uvcg_frame *frm = priv1;
		काष्ठा uvc_descriptor_header *h = *dest;

		sz = माप(frm->frame);
		स_नकल(*dest, &frm->frame, sz);
		*dest += sz;
		sz = frm->frame.b_frame_पूर्णांकerval_type *
			माप(*frm->dw_frame_पूर्णांकerval);
		स_नकल(*dest, frm->dw_frame_पूर्णांकerval, sz);
		*dest += sz;
		अगर (frm->fmt_type == UVCG_UNCOMPRESSED)
			h->bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(
				frm->frame.b_frame_पूर्णांकerval_type);
		अन्यथा अगर (frm->fmt_type == UVCG_MJPEG)
			h->bLength = UVC_DT_FRAME_MJPEG_SIZE(
				frm->frame.b_frame_पूर्णांकerval_type);
	पूर्ण
	अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvcg_streaming_class_allow_link(काष्ठा config_item *src,
					   काष्ठा config_item *target)
अणु
	काष्ठा config_item *streaming, *header;
	काष्ठा f_uvc_opts *opts;
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा uvc_descriptor_header ***class_array, **cl_arr;
	काष्ठा uvcg_streaming_header *target_hdr;
	व्योम *data, *data_save;
	माप_प्रकार size = 0, count = 0;
	पूर्णांक ret = -EINVAL;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	streaming = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(streaming), "header");
	अगर (!header || target->ci_parent != header)
		जाओ out;

	opts = to_f_uvc_opts(streaming->ci_parent);

	mutex_lock(&opts->lock);

	class_array = __uvcg_get_stream_class_arr(src, opts);
	अगर (!class_array || *class_array || opts->refcnt) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	target_hdr = to_uvcg_streaming_header(target);
	ret = __uvcg_iter_strm_cls(target_hdr, &size, &count, __uvcg_cnt_strm);
	अगर (ret)
		जाओ unlock;

	count += 2; /* color_matching, शून्य */
	*class_array = kसुस्मृति(count, माप(व्योम *), GFP_KERNEL);
	अगर (!*class_array) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	data = data_save = kzalloc(size, GFP_KERNEL);
	अगर (!data) अणु
		kमुक्त(*class_array);
		*class_array = शून्य;
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	cl_arr = *class_array;
	ret = __uvcg_iter_strm_cls(target_hdr, &data, &cl_arr,
				   __uvcg_fill_strm);
	अगर (ret) अणु
		kमुक्त(*class_array);
		*class_array = शून्य;
		/*
		 * __uvcg_fill_strm() called from __uvcg_iter_stream_cls()
		 * might have advanced the "data", so use a backup copy
		 */
		kमुक्त(data_save);
		जाओ unlock;
	पूर्ण
	*cl_arr = (काष्ठा uvc_descriptor_header *)&opts->uvc_color_matching;

	++target_hdr->linked;
	ret = 0;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
	वापस ret;
पूर्ण

अटल व्योम uvcg_streaming_class_drop_link(काष्ठा config_item *src,
					  काष्ठा config_item *target)
अणु
	काष्ठा config_item *streaming, *header;
	काष्ठा f_uvc_opts *opts;
	काष्ठा mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	काष्ठा uvc_descriptor_header ***class_array;
	काष्ठा uvcg_streaming_header *target_hdr;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	streaming = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(streaming), "header");
	अगर (!header || target->ci_parent != header)
		जाओ out;

	opts = to_f_uvc_opts(streaming->ci_parent);

	mutex_lock(&opts->lock);

	class_array = __uvcg_get_stream_class_arr(src, opts);
	अगर (!class_array || !*class_array)
		जाओ unlock;

	अगर (opts->refcnt)
		जाओ unlock;

	target_hdr = to_uvcg_streaming_header(target);
	--target_hdr->linked;
	kमुक्त(**class_array);
	kमुक्त(*class_array);
	*class_array = शून्य;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
पूर्ण

अटल काष्ठा configfs_item_operations uvcg_streaming_class_item_ops = अणु
	.release	= uvcg_config_item_release,
	.allow_link	= uvcg_streaming_class_allow_link,
	.drop_link	= uvcg_streaming_class_drop_link,
पूर्ण;

अटल स्थिर काष्ठा config_item_type uvcg_streaming_class_type = अणु
	.ct_item_ops	= &uvcg_streaming_class_item_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming/class
 */

अटल पूर्णांक uvcg_streaming_class_create_children(काष्ठा config_group *parent)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु "fs", "hs", "ss" पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(names); ++i) अणु
		काष्ठा uvcg_streaming_class_group *group;

		group = kzalloc(माप(*group), GFP_KERNEL);
		अगर (!group)
			वापस -ENOMEM;

		group->name = names[i];

		config_group_init_type_name(&group->group, group->name,
					    &uvcg_streaming_class_type);
		configfs_add_शेष_group(&group->group, parent);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_streaming_class_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "class",
	.create_children = uvcg_streaming_class_create_children,
पूर्ण;

/* -----------------------------------------------------------------------------
 * streaming
 */

अटल sमाप_प्रकार uvcg_शेष_streaming_b_पूर्णांकerface_number_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा config_group *group = to_config_group(item);
	काष्ठा mutex *su_mutex = &group->cg_subsys->su_mutex;
	काष्ठा config_item *opts_item;
	काष्ठा f_uvc_opts *opts;
	पूर्णांक result = 0;

	mutex_lock(su_mutex); /* क्रम navigating configfs hierarchy */

	opts_item = item->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result += प्र_लिखो(page, "%u\n", opts->streaming_पूर्णांकerface);
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);

	वापस result;
पूर्ण

UVC_ATTR_RO(uvcg_शेष_streaming_, b_पूर्णांकerface_number, bInterfaceNumber);

अटल काष्ठा configfs_attribute *uvcg_शेष_streaming_attrs[] = अणु
	&uvcg_शेष_streaming_attr_b_पूर्णांकerface_number,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvcg_streaming_grp_type = अणु
	.type = अणु
		.ct_item_ops	= &uvcg_config_item_ops,
		.ct_attrs	= uvcg_शेष_streaming_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "streaming",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_streaming_header_grp_type,
		&uvcg_uncompressed_grp_type,
		&uvcg_mjpeg_grp_type,
		&uvcg_color_matching_grp_type,
		&uvcg_streaming_class_grp_type,
		शून्य,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * UVC function
 */

अटल व्योम uvc_func_item_release(काष्ठा config_item *item)
अणु
	काष्ठा f_uvc_opts *opts = to_f_uvc_opts(item);

	uvcg_config_हटाओ_children(to_config_group(item));
	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations uvc_func_item_ops = अणु
	.release	= uvc_func_item_release,
पूर्ण;

#घोषणा UVCG_OPTS_ATTR(cname, aname, limit)				\
अटल sमाप_प्रकार f_uvc_opts_##cname##_show(				\
	काष्ठा config_item *item, अक्षर *page)				\
अणु									\
	काष्ठा f_uvc_opts *opts = to_f_uvc_opts(item);			\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", opts->cname);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार								\
f_uvc_opts_##cname##_store(काष्ठा config_item *item,			\
			   स्थिर अक्षर *page, माप_प्रकार len)		\
अणु									\
	काष्ठा f_uvc_opts *opts = to_f_uvc_opts(item);			\
	अचिन्हित पूर्णांक num;						\
	पूर्णांक ret;							\
									\
	mutex_lock(&opts->lock);					\
	अगर (opts->refcnt) अणु						\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtouपूर्णांक(page, 0, &num);				\
	अगर (ret)							\
		जाओ end;						\
									\
	अगर (num > limit) अणु						\
		ret = -EINVAL;						\
		जाओ end;						\
	पूर्ण								\
	opts->cname = num;						\
	ret = len;							\
end:									\
	mutex_unlock(&opts->lock);					\
	वापस ret;							\
पूर्ण									\
									\
UVC_ATTR(f_uvc_opts_, cname, cname)

UVCG_OPTS_ATTR(streaming_पूर्णांकerval, streaming_पूर्णांकerval, 16);
UVCG_OPTS_ATTR(streaming_maxpacket, streaming_maxpacket, 3072);
UVCG_OPTS_ATTR(streaming_maxburst, streaming_maxburst, 15);

#अघोषित UVCG_OPTS_ATTR

अटल काष्ठा configfs_attribute *uvc_attrs[] = अणु
	&f_uvc_opts_attr_streaming_पूर्णांकerval,
	&f_uvc_opts_attr_streaming_maxpacket,
	&f_uvc_opts_attr_streaming_maxburst,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvcg_config_group_type uvc_func_type = अणु
	.type = अणु
		.ct_item_ops	= &uvc_func_item_ops,
		.ct_attrs	= uvc_attrs,
		.ct_owner	= THIS_MODULE,
	पूर्ण,
	.name = "",
	.children = (स्थिर काष्ठा uvcg_config_group_type*[]) अणु
		&uvcg_control_grp_type,
		&uvcg_streaming_grp_type,
		शून्य,
	पूर्ण,
पूर्ण;

पूर्णांक uvcg_attach_configfs(काष्ठा f_uvc_opts *opts)
अणु
	पूर्णांक ret;

	config_group_init_type_name(&opts->func_inst.group, uvc_func_type.name,
				    &uvc_func_type.type);

	ret = uvcg_config_create_children(&opts->func_inst.group,
					  &uvc_func_type);
	अगर (ret < 0)
		config_group_put(&opts->func_inst.group);

	वापस ret;
पूर्ण
