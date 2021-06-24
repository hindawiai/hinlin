<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश "pvrusb2-sysfs.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-debug.h"
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
#समावेश "pvrusb2-debugifc.h"
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */

#घोषणा pvr2_sysfs_trace(...) pvr2_trace(PVR2_TRACE_SYSFS,__VA_ARGS__)

काष्ठा pvr2_sysfs अणु
	काष्ठा pvr2_channel channel;
	काष्ठा device *class_dev;
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
	काष्ठा pvr2_sysfs_debugअगरc *debugअगरc;
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */
	काष्ठा pvr2_sysfs_ctl_item *item_first;
	काष्ठा pvr2_sysfs_ctl_item *item_last;
	काष्ठा device_attribute attr_v4l_minor_number;
	काष्ठा device_attribute attr_v4l_radio_minor_number;
	काष्ठा device_attribute attr_unit_number;
	काष्ठा device_attribute attr_bus_info;
	काष्ठा device_attribute attr_hdw_name;
	काष्ठा device_attribute attr_hdw_desc;
	पूर्णांक v4l_minor_number_created_ok;
	पूर्णांक v4l_radio_minor_number_created_ok;
	पूर्णांक unit_number_created_ok;
	पूर्णांक bus_info_created_ok;
	पूर्णांक hdw_name_created_ok;
	पूर्णांक hdw_desc_created_ok;
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
काष्ठा pvr2_sysfs_debugअगरc अणु
	काष्ठा device_attribute attr_debugcmd;
	काष्ठा device_attribute attr_debuginfo;
	पूर्णांक debugcmd_created_ok;
	पूर्णांक debuginfo_created_ok;
पूर्ण;
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */

काष्ठा pvr2_sysfs_ctl_item अणु
	काष्ठा device_attribute attr_name;
	काष्ठा device_attribute attr_type;
	काष्ठा device_attribute attr_min;
	काष्ठा device_attribute attr_max;
	काष्ठा device_attribute attr_def;
	काष्ठा device_attribute attr_क्रमागत;
	काष्ठा device_attribute attr_bits;
	काष्ठा device_attribute attr_val;
	काष्ठा device_attribute attr_custom;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक ctl_id;
	काष्ठा pvr2_sysfs *chptr;
	काष्ठा pvr2_sysfs_ctl_item *item_next;
	काष्ठा attribute *attr_gen[8];
	काष्ठा attribute_group grp;
	पूर्णांक created_ok;
	अक्षर name[80];
पूर्ण;

काष्ठा pvr2_sysfs_class अणु
	काष्ठा class class;
पूर्ण;

अटल sमाप_प्रकार show_name(काष्ठा device *class_dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	स्थिर अक्षर *name;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_name);
	name = pvr2_ctrl_get_desc(cip->cptr);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_name(cid=%d) is %s",
			 cip->chptr, cip->ctl_id, name);
	अगर (!name) वापस -EINVAL;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", name);
पूर्ण

अटल sमाप_प्रकार show_type(काष्ठा device *class_dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	स्थिर अक्षर *name;
	क्रमागत pvr2_ctl_type tp;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_type);
	tp = pvr2_ctrl_get_type(cip->cptr);
	चयन (tp) अणु
	हाल pvr2_ctl_पूर्णांक: name = "integer"; अवरोध;
	हाल pvr2_ctl_क्रमागत: name = "enum"; अवरोध;
	हाल pvr2_ctl_biपंचांगask: name = "bitmask"; अवरोध;
	हाल pvr2_ctl_bool: name = "boolean"; अवरोध;
	शेष: name = "?"; अवरोध;
	पूर्ण
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_type(cid=%d) is %s",
			 cip->chptr, cip->ctl_id, name);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", name);
पूर्ण

अटल sमाप_प्रकार show_min(काष्ठा device *class_dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	दीर्घ val;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_min);
	val = pvr2_ctrl_get_min(cip->cptr);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_min(cid=%d) is %ld",
			 cip->chptr, cip->ctl_id, val);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%ld\n", val);
पूर्ण

अटल sमाप_प्रकार show_max(काष्ठा device *class_dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	दीर्घ val;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_max);
	val = pvr2_ctrl_get_max(cip->cptr);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_max(cid=%d) is %ld",
			 cip->chptr, cip->ctl_id, val);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%ld\n", val);
पूर्ण

अटल sमाप_प्रकार show_def(काष्ठा device *class_dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक cnt = 0;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_def);
	ret = pvr2_ctrl_get_def(cip->cptr, &val);
	अगर (ret < 0) वापस ret;
	ret = pvr2_ctrl_value_to_sym(cip->cptr, ~0, val,
				     buf, PAGE_SIZE - 1, &cnt);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_def(cid=%d) is %.*s (%d)",
			 cip->chptr, cip->ctl_id, cnt, buf, val);
	buf[cnt] = '\n';
	वापस cnt + 1;
पूर्ण

अटल sमाप_प्रकार show_val_norm(काष्ठा device *class_dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक cnt = 0;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_val);
	ret = pvr2_ctrl_get_value(cip->cptr, &val);
	अगर (ret < 0) वापस ret;
	ret = pvr2_ctrl_value_to_sym(cip->cptr, ~0, val,
				     buf, PAGE_SIZE - 1, &cnt);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_val_norm(cid=%d) is %.*s (%d)",
			 cip->chptr, cip->ctl_id, cnt, buf, val);
	buf[cnt] = '\n';
	वापस cnt+1;
पूर्ण

अटल sमाप_प्रकार show_val_custom(काष्ठा device *class_dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक cnt = 0;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_custom);
	ret = pvr2_ctrl_get_value(cip->cptr, &val);
	अगर (ret < 0) वापस ret;
	ret = pvr2_ctrl_custom_value_to_sym(cip->cptr, ~0, val,
					    buf, PAGE_SIZE - 1, &cnt);
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_val_custom(cid=%d) is %.*s (%d)",
			 cip->chptr, cip->ctl_id, cnt, buf, val);
	buf[cnt] = '\n';
	वापस cnt+1;
पूर्ण

अटल sमाप_प्रकार show_क्रमागत(काष्ठा device *class_dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	दीर्घ val;
	अचिन्हित पूर्णांक bcnt, ccnt, ecnt;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_क्रमागत);
	ecnt = pvr2_ctrl_get_cnt(cip->cptr);
	bcnt = 0;
	क्रम (val = 0; val < ecnt; val++) अणु
		pvr2_ctrl_get_valname(cip->cptr, val, buf + bcnt,
				      PAGE_SIZE - bcnt, &ccnt);
		अगर (!ccnt) जारी;
		bcnt += ccnt;
		अगर (bcnt >= PAGE_SIZE) अवरोध;
		buf[bcnt] = '\n';
		bcnt++;
	पूर्ण
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_enum(cid=%d)",
			 cip->chptr, cip->ctl_id);
	वापस bcnt;
पूर्ण

अटल sमाप_प्रकार show_bits(काष्ठा device *class_dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक valid_bits, msk;
	अचिन्हित पूर्णांक bcnt, ccnt;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_bits);
	valid_bits = pvr2_ctrl_get_mask(cip->cptr);
	bcnt = 0;
	क्रम (msk = 1; valid_bits; msk <<= 1) अणु
		अगर (!(msk & valid_bits)) जारी;
		valid_bits &= ~msk;
		pvr2_ctrl_get_valname(cip->cptr, msk, buf + bcnt,
				      PAGE_SIZE - bcnt, &ccnt);
		bcnt += ccnt;
		अगर (bcnt >= PAGE_SIZE) अवरोध;
		buf[bcnt] = '\n';
		bcnt++;
	पूर्ण
	pvr2_sysfs_trace("pvr2_sysfs(%p) show_bits(cid=%d)",
			 cip->chptr, cip->ctl_id);
	वापस bcnt;
पूर्ण

अटल पूर्णांक store_val_any(काष्ठा pvr2_sysfs_ctl_item *cip, पूर्णांक customfl,
			 स्थिर अक्षर *buf,अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;
	पूर्णांक mask,val;
	अगर (customfl) अणु
		ret = pvr2_ctrl_custom_sym_to_value(cip->cptr, buf, count,
						    &mask, &val);
	पूर्ण अन्यथा अणु
		ret = pvr2_ctrl_sym_to_value(cip->cptr, buf, count,
					     &mask, &val);
	पूर्ण
	अगर (ret < 0) वापस ret;
	ret = pvr2_ctrl_set_mask_value(cip->cptr, mask, val);
	pvr2_hdw_commit_ctl(cip->chptr->channel.hdw);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_val_norm(काष्ठा device *class_dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक ret;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_val);
	pvr2_sysfs_trace("pvr2_sysfs(%p) store_val_norm(cid=%d) \"%.*s\"",
			 cip->chptr, cip->ctl_id, (पूर्णांक)count, buf);
	ret = store_val_any(cip, 0, buf, count);
	अगर (!ret) ret = count;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_val_custom(काष्ठा device *class_dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	पूर्णांक ret;
	cip = container_of(attr, काष्ठा pvr2_sysfs_ctl_item, attr_custom);
	pvr2_sysfs_trace("pvr2_sysfs(%p) store_val_custom(cid=%d) \"%.*s\"",
			 cip->chptr, cip->ctl_id, (पूर्णांक)count, buf);
	ret = store_val_any(cip, 1, buf, count);
	अगर (!ret) ret = count;
	वापस ret;
पूर्ण

अटल व्योम pvr2_sysfs_add_control(काष्ठा pvr2_sysfs *sfp,पूर्णांक ctl_id)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip;
	काष्ठा pvr2_ctrl *cptr;
	अचिन्हित पूर्णांक cnt,acnt;
	पूर्णांक ret;

	cptr = pvr2_hdw_get_ctrl_by_index(sfp->channel.hdw,ctl_id);
	अगर (!cptr) वापस;

	cip = kzalloc(माप(*cip),GFP_KERNEL);
	अगर (!cip) वापस;
	pvr2_sysfs_trace("Creating pvr2_sysfs_ctl_item id=%p",cip);

	cip->cptr = cptr;
	cip->ctl_id = ctl_id;

	cip->chptr = sfp;
	cip->item_next = शून्य;
	अगर (sfp->item_last) अणु
		sfp->item_last->item_next = cip;
	पूर्ण अन्यथा अणु
		sfp->item_first = cip;
	पूर्ण
	sfp->item_last = cip;

	sysfs_attr_init(&cip->attr_name.attr);
	cip->attr_name.attr.name = "name";
	cip->attr_name.attr.mode = S_IRUGO;
	cip->attr_name.show = show_name;

	sysfs_attr_init(&cip->attr_type.attr);
	cip->attr_type.attr.name = "type";
	cip->attr_type.attr.mode = S_IRUGO;
	cip->attr_type.show = show_type;

	sysfs_attr_init(&cip->attr_min.attr);
	cip->attr_min.attr.name = "min_val";
	cip->attr_min.attr.mode = S_IRUGO;
	cip->attr_min.show = show_min;

	sysfs_attr_init(&cip->attr_max.attr);
	cip->attr_max.attr.name = "max_val";
	cip->attr_max.attr.mode = S_IRUGO;
	cip->attr_max.show = show_max;

	sysfs_attr_init(&cip->attr_def.attr);
	cip->attr_def.attr.name = "def_val";
	cip->attr_def.attr.mode = S_IRUGO;
	cip->attr_def.show = show_def;

	sysfs_attr_init(&cip->attr_val.attr);
	cip->attr_val.attr.name = "cur_val";
	cip->attr_val.attr.mode = S_IRUGO;

	sysfs_attr_init(&cip->attr_custom.attr);
	cip->attr_custom.attr.name = "custom_val";
	cip->attr_custom.attr.mode = S_IRUGO;

	sysfs_attr_init(&cip->attr_क्रमागत.attr);
	cip->attr_क्रमागत.attr.name = "enum_val";
	cip->attr_क्रमागत.attr.mode = S_IRUGO;
	cip->attr_क्रमागत.show = show_क्रमागत;

	sysfs_attr_init(&cip->attr_bits.attr);
	cip->attr_bits.attr.name = "bit_val";
	cip->attr_bits.attr.mode = S_IRUGO;
	cip->attr_bits.show = show_bits;

	अगर (pvr2_ctrl_is_writable(cptr)) अणु
		cip->attr_val.attr.mode |= S_IWUSR|S_IWGRP;
		cip->attr_custom.attr.mode |= S_IWUSR|S_IWGRP;
	पूर्ण

	acnt = 0;
	cip->attr_gen[acnt++] = &cip->attr_name.attr;
	cip->attr_gen[acnt++] = &cip->attr_type.attr;
	cip->attr_gen[acnt++] = &cip->attr_val.attr;
	cip->attr_gen[acnt++] = &cip->attr_def.attr;
	cip->attr_val.show = show_val_norm;
	cip->attr_val.store = store_val_norm;
	अगर (pvr2_ctrl_has_custom_symbols(cptr)) अणु
		cip->attr_gen[acnt++] = &cip->attr_custom.attr;
		cip->attr_custom.show = show_val_custom;
		cip->attr_custom.store = store_val_custom;
	पूर्ण
	चयन (pvr2_ctrl_get_type(cptr)) अणु
	हाल pvr2_ctl_क्रमागत:
		// Control is an क्रमागतeration
		cip->attr_gen[acnt++] = &cip->attr_क्रमागत.attr;
		अवरोध;
	हाल pvr2_ctl_पूर्णांक:
		// Control is an पूर्णांकeger
		cip->attr_gen[acnt++] = &cip->attr_min.attr;
		cip->attr_gen[acnt++] = &cip->attr_max.attr;
		अवरोध;
	हाल pvr2_ctl_biपंचांगask:
		// Control is an biपंचांगask
		cip->attr_gen[acnt++] = &cip->attr_bits.attr;
		अवरोध;
	शेष: अवरोध;
	पूर्ण

	cnt = scnम_लिखो(cip->name,माप(cip->name)-1,"ctl_%s",
			pvr2_ctrl_get_name(cptr));
	cip->name[cnt] = 0;
	cip->grp.name = cip->name;
	cip->grp.attrs = cip->attr_gen;

	ret = sysfs_create_group(&sfp->class_dev->kobj,&cip->grp);
	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "sysfs_create_group error: %d",
			   ret);
		वापस;
	पूर्ण
	cip->created_ok = !0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
अटल sमाप_प्रकार debuginfo_show(काष्ठा device *, काष्ठा device_attribute *,
			      अक्षर *);
अटल sमाप_प्रकार debugcmd_show(काष्ठा device *, काष्ठा device_attribute *,
			     अक्षर *);
अटल sमाप_प्रकार debugcmd_store(काष्ठा device *, काष्ठा device_attribute *,
			      स्थिर अक्षर *, माप_प्रकार count);

अटल व्योम pvr2_sysfs_add_debugअगरc(काष्ठा pvr2_sysfs *sfp)
अणु
	काष्ठा pvr2_sysfs_debugअगरc *dip;
	पूर्णांक ret;

	dip = kzalloc(माप(*dip),GFP_KERNEL);
	अगर (!dip) वापस;
	sysfs_attr_init(&dip->attr_debugcmd.attr);
	dip->attr_debugcmd.attr.name = "debugcmd";
	dip->attr_debugcmd.attr.mode = S_IRUGO|S_IWUSR|S_IWGRP;
	dip->attr_debugcmd.show = debugcmd_show;
	dip->attr_debugcmd.store = debugcmd_store;
	sysfs_attr_init(&dip->attr_debuginfo.attr);
	dip->attr_debuginfo.attr.name = "debuginfo";
	dip->attr_debuginfo.attr.mode = S_IRUGO;
	dip->attr_debuginfo.show = debuginfo_show;
	sfp->debugअगरc = dip;
	ret = device_create_file(sfp->class_dev,&dip->attr_debugcmd);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		dip->debugcmd_created_ok = !0;
	पूर्ण
	ret = device_create_file(sfp->class_dev,&dip->attr_debuginfo);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		dip->debuginfo_created_ok = !0;
	पूर्ण
पूर्ण


अटल व्योम pvr2_sysfs_tear_करोwn_debugअगरc(काष्ठा pvr2_sysfs *sfp)
अणु
	अगर (!sfp->debugअगरc) वापस;
	अगर (sfp->debugअगरc->debuginfo_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->debugअगरc->attr_debuginfo);
	पूर्ण
	अगर (sfp->debugअगरc->debugcmd_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->debugअगरc->attr_debugcmd);
	पूर्ण
	kमुक्त(sfp->debugअगरc);
	sfp->debugअगरc = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */


अटल व्योम pvr2_sysfs_add_controls(काष्ठा pvr2_sysfs *sfp)
अणु
	अचिन्हित पूर्णांक idx,cnt;
	cnt = pvr2_hdw_get_ctrl_count(sfp->channel.hdw);
	क्रम (idx = 0; idx < cnt; idx++) अणु
		pvr2_sysfs_add_control(sfp,idx);
	पूर्ण
पूर्ण


अटल व्योम pvr2_sysfs_tear_करोwn_controls(काष्ठा pvr2_sysfs *sfp)
अणु
	काष्ठा pvr2_sysfs_ctl_item *cip1,*cip2;
	क्रम (cip1 = sfp->item_first; cip1; cip1 = cip2) अणु
		cip2 = cip1->item_next;
		अगर (cip1->created_ok) अणु
			sysfs_हटाओ_group(&sfp->class_dev->kobj,&cip1->grp);
		पूर्ण
		pvr2_sysfs_trace("Destroying pvr2_sysfs_ctl_item id=%p",cip1);
		kमुक्त(cip1);
	पूर्ण
पूर्ण


अटल व्योम pvr2_sysfs_class_release(काष्ठा class *class)
अणु
	काष्ठा pvr2_sysfs_class *clp;
	clp = container_of(class,काष्ठा pvr2_sysfs_class,class);
	pvr2_sysfs_trace("Destroying pvr2_sysfs_class id=%p",clp);
	kमुक्त(clp);
पूर्ण


अटल व्योम pvr2_sysfs_release(काष्ठा device *class_dev)
अणु
	pvr2_sysfs_trace("Releasing class_dev id=%p",class_dev);
	kमुक्त(class_dev);
पूर्ण


अटल व्योम class_dev_destroy(काष्ठा pvr2_sysfs *sfp)
अणु
	काष्ठा device *dev;
	अगर (!sfp->class_dev) वापस;
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
	pvr2_sysfs_tear_करोwn_debugअगरc(sfp);
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */
	pvr2_sysfs_tear_करोwn_controls(sfp);
	अगर (sfp->hdw_desc_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
				   &sfp->attr_hdw_desc);
	पूर्ण
	अगर (sfp->hdw_name_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
				   &sfp->attr_hdw_name);
	पूर्ण
	अगर (sfp->bus_info_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->attr_bus_info);
	पूर्ण
	अगर (sfp->v4l_minor_number_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->attr_v4l_minor_number);
	पूर्ण
	अगर (sfp->v4l_radio_minor_number_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->attr_v4l_radio_minor_number);
	पूर्ण
	अगर (sfp->unit_number_created_ok) अणु
		device_हटाओ_file(sfp->class_dev,
					 &sfp->attr_unit_number);
	पूर्ण
	pvr2_sysfs_trace("Destroying class_dev id=%p",sfp->class_dev);
	dev_set_drvdata(sfp->class_dev, शून्य);
	dev = sfp->class_dev->parent;
	sfp->class_dev->parent = शून्य;
	put_device(dev);
	device_unरेजिस्टर(sfp->class_dev);
	sfp->class_dev = शून्य;
पूर्ण


अटल sमाप_प्रकार v4l_minor_number_show(काष्ठा device *class_dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%d\n",
			 pvr2_hdw_v4l_get_minor_number(sfp->channel.hdw,
						       pvr2_v4l_type_video));
पूर्ण


अटल sमाप_प्रकार bus_info_show(काष्ठा device *class_dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%s\n",
			 pvr2_hdw_get_bus_info(sfp->channel.hdw));
पूर्ण


अटल sमाप_प्रकार hdw_name_show(काष्ठा device *class_dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%s\n",
			 pvr2_hdw_get_type(sfp->channel.hdw));
पूर्ण


अटल sमाप_प्रकार hdw_desc_show(काष्ठा device *class_dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%s\n",
			 pvr2_hdw_get_desc(sfp->channel.hdw));
पूर्ण


अटल sमाप_प्रकार v4l_radio_minor_number_show(काष्ठा device *class_dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%d\n",
			 pvr2_hdw_v4l_get_minor_number(sfp->channel.hdw,
						       pvr2_v4l_type_radio));
पूर्ण


अटल sमाप_प्रकार unit_number_show(काष्ठा device *class_dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस scnम_लिखो(buf,PAGE_SIZE,"%d\n",
			 pvr2_hdw_get_unit_number(sfp->channel.hdw));
पूर्ण


अटल व्योम class_dev_create(काष्ठा pvr2_sysfs *sfp,
			     काष्ठा pvr2_sysfs_class *class_ptr)
अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा device *class_dev;
	पूर्णांक ret;

	usb_dev = pvr2_hdw_get_dev(sfp->channel.hdw);
	अगर (!usb_dev) वापस;
	class_dev = kzalloc(माप(*class_dev),GFP_KERNEL);
	अगर (!class_dev) वापस;

	pvr2_sysfs_trace("Creating class_dev id=%p",class_dev);

	class_dev->class = &class_ptr->class;

	dev_set_name(class_dev, "%s",
		     pvr2_hdw_get_device_identअगरier(sfp->channel.hdw));

	class_dev->parent = get_device(&usb_dev->dev);

	sfp->class_dev = class_dev;
	dev_set_drvdata(class_dev, sfp);
	ret = device_रेजिस्टर(class_dev);
	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_register failed");
		put_device(class_dev);
		वापस;
	पूर्ण

	sysfs_attr_init(&sfp->attr_v4l_minor_number.attr);
	sfp->attr_v4l_minor_number.attr.name = "v4l_minor_number";
	sfp->attr_v4l_minor_number.attr.mode = S_IRUGO;
	sfp->attr_v4l_minor_number.show = v4l_minor_number_show;
	sfp->attr_v4l_minor_number.store = शून्य;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_v4l_minor_number);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->v4l_minor_number_created_ok = !0;
	पूर्ण

	sysfs_attr_init(&sfp->attr_v4l_radio_minor_number.attr);
	sfp->attr_v4l_radio_minor_number.attr.name = "v4l_radio_minor_number";
	sfp->attr_v4l_radio_minor_number.attr.mode = S_IRUGO;
	sfp->attr_v4l_radio_minor_number.show = v4l_radio_minor_number_show;
	sfp->attr_v4l_radio_minor_number.store = शून्य;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_v4l_radio_minor_number);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->v4l_radio_minor_number_created_ok = !0;
	पूर्ण

	sysfs_attr_init(&sfp->attr_unit_number.attr);
	sfp->attr_unit_number.attr.name = "unit_number";
	sfp->attr_unit_number.attr.mode = S_IRUGO;
	sfp->attr_unit_number.show = unit_number_show;
	sfp->attr_unit_number.store = शून्य;
	ret = device_create_file(sfp->class_dev,&sfp->attr_unit_number);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->unit_number_created_ok = !0;
	पूर्ण

	sysfs_attr_init(&sfp->attr_bus_info.attr);
	sfp->attr_bus_info.attr.name = "bus_info_str";
	sfp->attr_bus_info.attr.mode = S_IRUGO;
	sfp->attr_bus_info.show = bus_info_show;
	sfp->attr_bus_info.store = शून्य;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_bus_info);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->bus_info_created_ok = !0;
	पूर्ण

	sysfs_attr_init(&sfp->attr_hdw_name.attr);
	sfp->attr_hdw_name.attr.name = "device_hardware_type";
	sfp->attr_hdw_name.attr.mode = S_IRUGO;
	sfp->attr_hdw_name.show = hdw_name_show;
	sfp->attr_hdw_name.store = शून्य;
	ret = device_create_file(sfp->class_dev,
				 &sfp->attr_hdw_name);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->hdw_name_created_ok = !0;
	पूर्ण

	sysfs_attr_init(&sfp->attr_hdw_desc.attr);
	sfp->attr_hdw_desc.attr.name = "device_hardware_description";
	sfp->attr_hdw_desc.attr.mode = S_IRUGO;
	sfp->attr_hdw_desc.show = hdw_desc_show;
	sfp->attr_hdw_desc.store = शून्य;
	ret = device_create_file(sfp->class_dev,
				 &sfp->attr_hdw_desc);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	पूर्ण अन्यथा अणु
		sfp->hdw_desc_created_ok = !0;
	पूर्ण

	pvr2_sysfs_add_controls(sfp);
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
	pvr2_sysfs_add_debugअगरc(sfp);
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */
पूर्ण


अटल व्योम pvr2_sysfs_पूर्णांकernal_check(काष्ठा pvr2_channel *chp)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = container_of(chp,काष्ठा pvr2_sysfs,channel);
	अगर (!sfp->channel.mc_head->disconnect_flag) वापस;
	pvr2_trace(PVR2_TRACE_STRUCT,"Destroying pvr2_sysfs id=%p",sfp);
	class_dev_destroy(sfp);
	pvr2_channel_करोne(&sfp->channel);
	kमुक्त(sfp);
पूर्ण


काष्ठा pvr2_sysfs *pvr2_sysfs_create(काष्ठा pvr2_context *mp,
				     काष्ठा pvr2_sysfs_class *class_ptr)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = kzalloc(माप(*sfp),GFP_KERNEL);
	अगर (!sfp) वापस sfp;
	pvr2_trace(PVR2_TRACE_STRUCT,"Creating pvr2_sysfs id=%p",sfp);
	pvr2_channel_init(&sfp->channel,mp);
	sfp->channel.check_func = pvr2_sysfs_पूर्णांकernal_check;

	class_dev_create(sfp,class_ptr);
	वापस sfp;
पूर्ण



काष्ठा pvr2_sysfs_class *pvr2_sysfs_class_create(व्योम)
अणु
	काष्ठा pvr2_sysfs_class *clp;
	clp = kzalloc(माप(*clp),GFP_KERNEL);
	अगर (!clp) वापस clp;
	pvr2_sysfs_trace("Creating and registering pvr2_sysfs_class id=%p",
			 clp);
	clp->class.name = "pvrusb2";
	clp->class.class_release = pvr2_sysfs_class_release;
	clp->class.dev_release = pvr2_sysfs_release;
	अगर (class_रेजिस्टर(&clp->class)) अणु
		pvr2_sysfs_trace(
			"Registration failed for pvr2_sysfs_class id=%p",clp);
		kमुक्त(clp);
		clp = शून्य;
	पूर्ण
	वापस clp;
पूर्ण


व्योम pvr2_sysfs_class_destroy(काष्ठा pvr2_sysfs_class *clp)
अणु
	pvr2_sysfs_trace("Unregistering pvr2_sysfs_class id=%p", clp);
	अगर (clp)
		class_unरेजिस्टर(&clp->class);
पूर्ण


#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DEBUGIFC
अटल sमाप_प्रकार debuginfo_show(काष्ठा device *class_dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	pvr2_hdw_trigger_module_log(sfp->channel.hdw);
	वापस pvr2_debugअगरc_prपूर्णांक_info(sfp->channel.hdw,buf,PAGE_SIZE);
पूर्ण


अटल sमाप_प्रकार debugcmd_show(काष्ठा device *class_dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;
	वापस pvr2_debugअगरc_prपूर्णांक_status(sfp->channel.hdw,buf,PAGE_SIZE);
पूर्ण


अटल sमाप_प्रकार debugcmd_store(काष्ठा device *class_dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pvr2_sysfs *sfp;
	पूर्णांक ret;

	sfp = dev_get_drvdata(class_dev);
	अगर (!sfp) वापस -EINVAL;

	ret = pvr2_debugअगरc_करोcmd(sfp->channel.hdw,buf,count);
	अगर (ret < 0) वापस ret;
	वापस count;
पूर्ण
#पूर्ण_अगर /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */
