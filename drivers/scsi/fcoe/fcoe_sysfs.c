<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2011 - 2012 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/प्रकार.स>

#समावेश <scsi/fcoe_sysfs.h>
#समावेश <scsi/libfcoe.h>

/*
 * OK to include local libfcoe.h क्रम debug_logging, but cannot include
 * <scsi/libfcoe.h> otherwise non-netdev based fcoe solutions would have
 * have to include more than fcoe_sysfs.h.
 */
#समावेश "libfcoe.h"

अटल atomic_t ctlr_num;
अटल atomic_t fcf_num;

/*
 * fcoe_fcf_dev_loss_पंचांगo: the शेष number of seconds that fcoe sysfs
 * should insulate the loss of a fcf.
 */
अटल अचिन्हित पूर्णांक fcoe_fcf_dev_loss_पंचांगo = 1800;  /* seconds */

module_param_named(fcf_dev_loss_पंचांगo, fcoe_fcf_dev_loss_पंचांगo,
		   uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(fcf_dev_loss_पंचांगo,
		 "Maximum number of seconds that libfcoe should"
		 " insulate the loss of a fcf. Once this value is"
		 " exceeded, the fcf is removed.");

/*
 * These are used by the fcoe_*_show_function routines, they
 * are पूर्णांकentionally placed in the .c file as they're not पूर्णांकended
 * क्रम use throughout the code.
 */
#घोषणा fcoe_ctlr_id(x)				\
	((x)->id)
#घोषणा fcoe_ctlr_work_q_name(x)		\
	((x)->work_q_name)
#घोषणा fcoe_ctlr_work_q(x)			\
	((x)->work_q)
#घोषणा fcoe_ctlr_devloss_work_q_name(x)	\
	((x)->devloss_work_q_name)
#घोषणा fcoe_ctlr_devloss_work_q(x)		\
	((x)->devloss_work_q)
#घोषणा fcoe_ctlr_mode(x)			\
	((x)->mode)
#घोषणा fcoe_ctlr_fcf_dev_loss_पंचांगo(x)		\
	((x)->fcf_dev_loss_पंचांगo)
#घोषणा fcoe_ctlr_link_fail(x)			\
	((x)->lesb.lesb_link_fail)
#घोषणा fcoe_ctlr_vlink_fail(x)			\
	((x)->lesb.lesb_vlink_fail)
#घोषणा fcoe_ctlr_miss_fka(x)			\
	((x)->lesb.lesb_miss_fka)
#घोषणा fcoe_ctlr_symb_err(x)			\
	((x)->lesb.lesb_symb_err)
#घोषणा fcoe_ctlr_err_block(x)			\
	((x)->lesb.lesb_err_block)
#घोषणा fcoe_ctlr_fcs_error(x)			\
	((x)->lesb.lesb_fcs_error)
#घोषणा fcoe_ctlr_enabled(x)			\
	((x)->enabled)
#घोषणा fcoe_fcf_state(x)			\
	((x)->state)
#घोषणा fcoe_fcf_fabric_name(x)			\
	((x)->fabric_name)
#घोषणा fcoe_fcf_चयन_name(x)			\
	((x)->चयन_name)
#घोषणा fcoe_fcf_fc_map(x)			\
	((x)->fc_map)
#घोषणा fcoe_fcf_vfid(x)			\
	((x)->vfid)
#घोषणा fcoe_fcf_mac(x)				\
	((x)->mac)
#घोषणा fcoe_fcf_priority(x)			\
	((x)->priority)
#घोषणा fcoe_fcf_fka_period(x)			\
	((x)->fka_period)
#घोषणा fcoe_fcf_dev_loss_पंचांगo(x)		\
	((x)->dev_loss_पंचांगo)
#घोषणा fcoe_fcf_selected(x)			\
	((x)->selected)
#घोषणा fcoe_fcf_vlan_id(x)			\
	((x)->vlan_id)

/*
 * dev_loss_पंचांगo attribute
 */
अटल पूर्णांक fcoe_str_to_dev_loss(स्थिर अक्षर *buf, अचिन्हित दीर्घ *val)
अणु
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, val);
	अगर (ret)
		वापस -EINVAL;
	/*
	 * Check क्रम overflow; dev_loss_पंचांगo is u32
	 */
	अगर (*val > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक fcoe_fcf_set_dev_loss_पंचांगo(काष्ठा fcoe_fcf_device *fcf,
				     अचिन्हित दीर्घ val)
अणु
	अगर ((fcf->state == FCOE_FCF_STATE_UNKNOWN) ||
	    (fcf->state == FCOE_FCF_STATE_DISCONNECTED) ||
	    (fcf->state == FCOE_FCF_STATE_DELETED))
		वापस -EBUSY;
	/*
	 * Check क्रम overflow; dev_loss_पंचांगo is u32
	 */
	अगर (val > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	fcoe_fcf_dev_loss_पंचांगo(fcf) = val;
	वापस 0;
पूर्ण

#घोषणा FCOE_DEVICE_ATTR(_prefix, _name, _mode, _show, _store)	\
काष्ठा device_attribute device_attr_fcoe_##_prefix##_##_name =	\
	__ATTR(_name, _mode, _show, _store)

#घोषणा fcoe_ctlr_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार show_fcoe_ctlr_device_##field(काष्ठा device *dev, \
					    काष्ठा device_attribute *attr, \
					    अक्षर *buf)			\
अणु									\
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);		\
	अगर (ctlr->f->get_fcoe_ctlr_##field)				\
		ctlr->f->get_fcoe_ctlr_##field(ctlr);			\
	वापस snम_लिखो(buf, sz, क्रमmat_string,				\
			cast fcoe_ctlr_##field(ctlr));			\
पूर्ण

#घोषणा fcoe_fcf_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार show_fcoe_fcf_device_##field(काष्ठा device *dev,	\
					   काष्ठा device_attribute *attr, \
					   अक्षर *buf)			\
अणु									\
	काष्ठा fcoe_fcf_device *fcf = dev_to_fcf(dev);			\
	काष्ठा fcoe_ctlr_device *ctlr = fcoe_fcf_dev_to_ctlr_dev(fcf);	\
	अगर (ctlr->f->get_fcoe_fcf_##field)				\
		ctlr->f->get_fcoe_fcf_##field(fcf);			\
	वापस snम_लिखो(buf, sz, क्रमmat_string,				\
			cast fcoe_fcf_##field(fcf));			\
पूर्ण

#घोषणा fcoe_ctlr_निजी_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार show_fcoe_ctlr_device_##field(काष्ठा device *dev, \
					    काष्ठा device_attribute *attr, \
					    अक्षर *buf)			\
अणु									\
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);		\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast fcoe_ctlr_##field(ctlr)); \
पूर्ण

#घोषणा fcoe_fcf_निजी_show_function(field, क्रमmat_string, sz, cast)	\
अटल sमाप_प्रकार show_fcoe_fcf_device_##field(काष्ठा device *dev,	\
					   काष्ठा device_attribute *attr, \
					   अक्षर *buf)			\
अणु								\
	काष्ठा fcoe_fcf_device *fcf = dev_to_fcf(dev);			\
	वापस snम_लिखो(buf, sz, क्रमmat_string, cast fcoe_fcf_##field(fcf)); \
पूर्ण

#घोषणा fcoe_ctlr_निजी_rd_attr(field, क्रमmat_string, sz)		\
	fcoe_ctlr_निजी_show_function(field, क्रमmat_string, sz, )	\
	अटल FCOE_DEVICE_ATTR(ctlr, field, S_IRUGO,			\
				show_fcoe_ctlr_device_##field, शून्य)

#घोषणा fcoe_ctlr_rd_attr(field, क्रमmat_string, sz)			\
	fcoe_ctlr_show_function(field, क्रमmat_string, sz, )		\
	अटल FCOE_DEVICE_ATTR(ctlr, field, S_IRUGO,			\
				show_fcoe_ctlr_device_##field, शून्य)

#घोषणा fcoe_fcf_rd_attr(field, क्रमmat_string, sz)			\
	fcoe_fcf_show_function(field, क्रमmat_string, sz, )		\
	अटल FCOE_DEVICE_ATTR(fcf, field, S_IRUGO,			\
				show_fcoe_fcf_device_##field, शून्य)

#घोषणा fcoe_fcf_निजी_rd_attr(field, क्रमmat_string, sz)		\
	fcoe_fcf_निजी_show_function(field, क्रमmat_string, sz, )	\
	अटल FCOE_DEVICE_ATTR(fcf, field, S_IRUGO,			\
				show_fcoe_fcf_device_##field, शून्य)

#घोषणा fcoe_ctlr_निजी_rd_attr_cast(field, क्रमmat_string, sz, cast)	\
	fcoe_ctlr_निजी_show_function(field, क्रमmat_string, sz, (cast)) \
	अटल FCOE_DEVICE_ATTR(ctlr, field, S_IRUGO,			\
				show_fcoe_ctlr_device_##field, शून्य)

#घोषणा fcoe_fcf_निजी_rd_attr_cast(field, क्रमmat_string, sz, cast)	\
	fcoe_fcf_निजी_show_function(field, क्रमmat_string, sz, (cast)) \
	अटल FCOE_DEVICE_ATTR(fcf, field, S_IRUGO,			\
				show_fcoe_fcf_device_##field, शून्य)

#घोषणा fcoe_क्रमागत_name_search(title, table_type, table)			\
अटल स्थिर अक्षर *get_fcoe_##title##_name(क्रमागत table_type table_key)	\
अणु									\
	अगर (table_key < 0 || table_key >= ARRAY_SIZE(table))		\
		वापस शून्य;						\
	वापस table[table_key];					\
पूर्ण

अटल अक्षर *fip_conn_type_names[] = अणु
	[ FIP_CONN_TYPE_UNKNOWN ] = "Unknown",
	[ FIP_CONN_TYPE_FABRIC ]  = "Fabric",
	[ FIP_CONN_TYPE_VN2VN ]   = "VN2VN",
पूर्ण;
fcoe_क्रमागत_name_search(ctlr_mode, fip_conn_type, fip_conn_type_names)

अटल क्रमागत fip_conn_type fcoe_parse_mode(स्थिर अक्षर *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fip_conn_type_names); i++) अणु
		अगर (strहालcmp(buf, fip_conn_type_names[i]) == 0)
			वापस i;
	पूर्ण

	वापस FIP_CONN_TYPE_UNKNOWN;
पूर्ण

अटल अक्षर *fcf_state_names[] = अणु
	[ FCOE_FCF_STATE_UNKNOWN ]      = "Unknown",
	[ FCOE_FCF_STATE_DISCONNECTED ] = "Disconnected",
	[ FCOE_FCF_STATE_CONNECTED ]    = "Connected",
पूर्ण;
fcoe_क्रमागत_name_search(fcf_state, fcf_state, fcf_state_names)
#घोषणा FCOE_FCF_STATE_MAX_NAMELEN 50

अटल sमाप_प्रकार show_fcf_state(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा fcoe_fcf_device *fcf = dev_to_fcf(dev);
	स्थिर अक्षर *name;
	name = get_fcoe_fcf_state_name(fcf->state);
	अगर (!name)
		वापस -EINVAL;
	वापस snम_लिखो(buf, FCOE_FCF_STATE_MAX_NAMELEN, "%s\n", name);
पूर्ण
अटल FCOE_DEVICE_ATTR(fcf, state, S_IRUGO, show_fcf_state, शून्य);

#घोषणा FCOE_MAX_MODENAME_LEN 20
अटल sमाप_प्रकार show_ctlr_mode(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	स्थिर अक्षर *name;

	name = get_fcoe_ctlr_mode_name(ctlr->mode);
	अगर (!name)
		वापस -EINVAL;
	वापस snम_लिखो(buf, FCOE_MAX_MODENAME_LEN,
			"%s\n", name);
पूर्ण

अटल sमाप_प्रकार store_ctlr_mode(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	अक्षर mode[FCOE_MAX_MODENAME_LEN + 1];

	अगर (count > FCOE_MAX_MODENAME_LEN)
		वापस -EINVAL;

	म_नकलन(mode, buf, count);

	अगर (mode[count - 1] == '\n')
		mode[count - 1] = '\0';
	अन्यथा
		mode[count] = '\0';

	चयन (ctlr->enabled) अणु
	हाल FCOE_CTLR_ENABLED:
		LIBFCOE_SYSFS_DBG(ctlr, "Cannot change mode when enabled.\n");
		वापस -EBUSY;
	हाल FCOE_CTLR_DISABLED:
		अगर (!ctlr->f->set_fcoe_ctlr_mode) अणु
			LIBFCOE_SYSFS_DBG(ctlr,
					  "Mode change not supported by LLD.\n");
			वापस -ENOTSUPP;
		पूर्ण

		ctlr->mode = fcoe_parse_mode(mode);
		अगर (ctlr->mode == FIP_CONN_TYPE_UNKNOWN) अणु
			LIBFCOE_SYSFS_DBG(ctlr, "Unknown mode %s provided.\n",
					  buf);
			वापस -EINVAL;
		पूर्ण

		ctlr->f->set_fcoe_ctlr_mode(ctlr);
		LIBFCOE_SYSFS_DBG(ctlr, "Mode changed to %s.\n", buf);

		वापस count;
	हाल FCOE_CTLR_UNUSED:
	शेष:
		LIBFCOE_SYSFS_DBG(ctlr, "Mode change not supported.\n");
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल FCOE_DEVICE_ATTR(ctlr, mode, S_IRUGO | S_IWUSR,
			show_ctlr_mode, store_ctlr_mode);

अटल sमाप_प्रकार store_ctlr_enabled(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	bool enabled;
	पूर्णांक rc;

	अगर (*buf == '1')
		enabled = true;
	अन्यथा अगर (*buf == '0')
		enabled = false;
	अन्यथा
		वापस -EINVAL;

	चयन (ctlr->enabled) अणु
	हाल FCOE_CTLR_ENABLED:
		अगर (enabled)
			वापस count;
		ctlr->enabled = FCOE_CTLR_DISABLED;
		अवरोध;
	हाल FCOE_CTLR_DISABLED:
		अगर (!enabled)
			वापस count;
		ctlr->enabled = FCOE_CTLR_ENABLED;
		अवरोध;
	हाल FCOE_CTLR_UNUSED:
		वापस -ENOTSUPP;
	पूर्ण

	rc = ctlr->f->set_fcoe_ctlr_enabled(ctlr);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल अक्षर *ctlr_enabled_state_names[] = अणु
	[ FCOE_CTLR_ENABLED ]  = "1",
	[ FCOE_CTLR_DISABLED ] = "0",
पूर्ण;
fcoe_क्रमागत_name_search(ctlr_enabled_state, ctlr_enabled_state,
		      ctlr_enabled_state_names)
#घोषणा FCOE_CTLR_ENABLED_MAX_NAMELEN 50

अटल sमाप_प्रकार show_ctlr_enabled_state(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	स्थिर अक्षर *name;

	name = get_fcoe_ctlr_enabled_state_name(ctlr->enabled);
	अगर (!name)
		वापस -EINVAL;
	वापस snम_लिखो(buf, FCOE_CTLR_ENABLED_MAX_NAMELEN,
			"%s\n", name);
पूर्ण

अटल FCOE_DEVICE_ATTR(ctlr, enabled, S_IRUGO | S_IWUSR,
			show_ctlr_enabled_state,
			store_ctlr_enabled);

अटल sमाप_प्रकार store_ctlr_fip_resp(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr);

	mutex_lock(&fip->ctlr_mutex);
	अगर ((buf[1] == '\0') || ((buf[1] == '\n') && (buf[2] == '\0'))) अणु
		अगर (buf[0] == '1') अणु
			fip->fip_resp = 1;
			mutex_unlock(&fip->ctlr_mutex);
			वापस count;
		पूर्ण
		अगर (buf[0] == '0') अणु
			fip->fip_resp = 0;
			mutex_unlock(&fip->ctlr_mutex);
			वापस count;
		पूर्ण
	पूर्ण
	mutex_unlock(&fip->ctlr_mutex);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार show_ctlr_fip_resp(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr);

	वापस प्र_लिखो(buf, "%d\n", fip->fip_resp ? 1 : 0);
पूर्ण

अटल FCOE_DEVICE_ATTR(ctlr, fip_vlan_responder, S_IRUGO | S_IWUSR,
			show_ctlr_fip_resp,
			store_ctlr_fip_resp);

अटल sमाप_प्रकार
fcoe_ctlr_var_store(u32 *var, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ v;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err || v > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	*var = v;

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_ctlr_r_a_tov(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	अगर (ctlr_dev->enabled == FCOE_CTLR_ENABLED)
		वापस -EBUSY;
	अगर (ctlr_dev->enabled == FCOE_CTLR_DISABLED)
		वापस fcoe_ctlr_var_store(&ctlr->lp->r_a_tov, buf, count);
	वापस -ENOTSUPP;
पूर्ण

अटल sमाप_प्रकार show_ctlr_r_a_tov(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	वापस प्र_लिखो(buf, "%d\n", ctlr->lp->r_a_tov);
पूर्ण

अटल FCOE_DEVICE_ATTR(ctlr, r_a_tov, S_IRUGO | S_IWUSR,
			show_ctlr_r_a_tov, store_ctlr_r_a_tov);

अटल sमाप_प्रकार store_ctlr_e_d_tov(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	अगर (ctlr_dev->enabled == FCOE_CTLR_ENABLED)
		वापस -EBUSY;
	अगर (ctlr_dev->enabled == FCOE_CTLR_DISABLED)
		वापस fcoe_ctlr_var_store(&ctlr->lp->e_d_tov, buf, count);
	वापस -ENOTSUPP;
पूर्ण

अटल sमाप_प्रकार show_ctlr_e_d_tov(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	वापस प्र_लिखो(buf, "%d\n", ctlr->lp->e_d_tov);
पूर्ण

अटल FCOE_DEVICE_ATTR(ctlr, e_d_tov, S_IRUGO | S_IWUSR,
			show_ctlr_e_d_tov, store_ctlr_e_d_tov);

अटल sमाप_प्रकार
store_निजी_fcoe_ctlr_fcf_dev_loss_पंचांगo(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	काष्ठा fcoe_fcf_device *fcf;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = fcoe_str_to_dev_loss(buf, &val);
	अगर (rc)
		वापस rc;

	fcoe_ctlr_fcf_dev_loss_पंचांगo(ctlr) = val;
	mutex_lock(&ctlr->lock);
	list_क्रम_each_entry(fcf, &ctlr->fcfs, peers)
		fcoe_fcf_set_dev_loss_पंचांगo(fcf, val);
	mutex_unlock(&ctlr->lock);
	वापस count;
पूर्ण
fcoe_ctlr_निजी_show_function(fcf_dev_loss_पंचांगo, "%d\n", 20, );
अटल FCOE_DEVICE_ATTR(ctlr, fcf_dev_loss_पंचांगo, S_IRUGO | S_IWUSR,
			show_fcoe_ctlr_device_fcf_dev_loss_पंचांगo,
			store_निजी_fcoe_ctlr_fcf_dev_loss_पंचांगo);

/* Link Error Status Block (LESB) */
fcoe_ctlr_rd_attr(link_fail, "%u\n", 20);
fcoe_ctlr_rd_attr(vlink_fail, "%u\n", 20);
fcoe_ctlr_rd_attr(miss_fka, "%u\n", 20);
fcoe_ctlr_rd_attr(symb_err, "%u\n", 20);
fcoe_ctlr_rd_attr(err_block, "%u\n", 20);
fcoe_ctlr_rd_attr(fcs_error, "%u\n", 20);

fcoe_fcf_निजी_rd_attr_cast(fabric_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fcoe_fcf_निजी_rd_attr_cast(चयन_name, "0x%llx\n", 20, अचिन्हित दीर्घ दीर्घ);
fcoe_fcf_निजी_rd_attr(priority, "%u\n", 20);
fcoe_fcf_निजी_rd_attr(fc_map, "0x%x\n", 20);
fcoe_fcf_निजी_rd_attr(vfid, "%u\n", 20);
fcoe_fcf_निजी_rd_attr(mac, "%pM\n", 20);
fcoe_fcf_निजी_rd_attr(fka_period, "%u\n", 20);
fcoe_fcf_rd_attr(selected, "%u\n", 20);
fcoe_fcf_rd_attr(vlan_id, "%u\n", 20);

fcoe_fcf_निजी_show_function(dev_loss_पंचांगo, "%d\n", 20, )
अटल sमाप_प्रकार
store_fcoe_fcf_dev_loss_पंचांगo(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fcoe_fcf_device *fcf = dev_to_fcf(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	rc = fcoe_str_to_dev_loss(buf, &val);
	अगर (rc)
		वापस rc;

	rc = fcoe_fcf_set_dev_loss_पंचांगo(fcf, val);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण
अटल FCOE_DEVICE_ATTR(fcf, dev_loss_पंचांगo, S_IRUGO | S_IWUSR,
			show_fcoe_fcf_device_dev_loss_पंचांगo,
			store_fcoe_fcf_dev_loss_पंचांगo);

अटल काष्ठा attribute *fcoe_ctlr_lesb_attrs[] = अणु
	&device_attr_fcoe_ctlr_link_fail.attr,
	&device_attr_fcoe_ctlr_vlink_fail.attr,
	&device_attr_fcoe_ctlr_miss_fka.attr,
	&device_attr_fcoe_ctlr_symb_err.attr,
	&device_attr_fcoe_ctlr_err_block.attr,
	&device_attr_fcoe_ctlr_fcs_error.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group fcoe_ctlr_lesb_attr_group = अणु
	.name = "lesb",
	.attrs = fcoe_ctlr_lesb_attrs,
पूर्ण;

अटल काष्ठा attribute *fcoe_ctlr_attrs[] = अणु
	&device_attr_fcoe_ctlr_fip_vlan_responder.attr,
	&device_attr_fcoe_ctlr_fcf_dev_loss_पंचांगo.attr,
	&device_attr_fcoe_ctlr_r_a_tov.attr,
	&device_attr_fcoe_ctlr_e_d_tov.attr,
	&device_attr_fcoe_ctlr_enabled.attr,
	&device_attr_fcoe_ctlr_mode.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group fcoe_ctlr_attr_group = अणु
	.attrs = fcoe_ctlr_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fcoe_ctlr_attr_groups[] = अणु
	&fcoe_ctlr_attr_group,
	&fcoe_ctlr_lesb_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *fcoe_fcf_attrs[] = अणु
	&device_attr_fcoe_fcf_fabric_name.attr,
	&device_attr_fcoe_fcf_चयन_name.attr,
	&device_attr_fcoe_fcf_dev_loss_पंचांगo.attr,
	&device_attr_fcoe_fcf_fc_map.attr,
	&device_attr_fcoe_fcf_vfid.attr,
	&device_attr_fcoe_fcf_mac.attr,
	&device_attr_fcoe_fcf_priority.attr,
	&device_attr_fcoe_fcf_fka_period.attr,
	&device_attr_fcoe_fcf_state.attr,
	&device_attr_fcoe_fcf_selected.attr,
	&device_attr_fcoe_fcf_vlan_id.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group fcoe_fcf_attr_group = अणु
	.attrs = fcoe_fcf_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fcoe_fcf_attr_groups[] = अणु
	&fcoe_fcf_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा bus_type fcoe_bus_type;

अटल पूर्णांक fcoe_bus_match(काष्ठा device *dev,
			  काष्ठा device_driver *drv)
अणु
	अगर (dev->bus == &fcoe_bus_type)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * fcoe_ctlr_device_release() - Release the FIP ctlr memory
 * @dev: Poपूर्णांकer to the FIP ctlr's embedded device
 *
 * Called when the last FIP ctlr reference is released.
 */
अटल व्योम fcoe_ctlr_device_release(काष्ठा device *dev)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	kमुक्त(ctlr);
पूर्ण

/**
 * fcoe_fcf_device_release() - Release the FIP fcf memory
 * @dev: Poपूर्णांकer to the fcf's embedded device
 *
 * Called when the last FIP fcf reference is released.
 */
अटल व्योम fcoe_fcf_device_release(काष्ठा device *dev)
अणु
	काष्ठा fcoe_fcf_device *fcf = dev_to_fcf(dev);
	kमुक्त(fcf);
पूर्ण

अटल स्थिर काष्ठा device_type fcoe_ctlr_device_type = अणु
	.name = "fcoe_ctlr",
	.groups = fcoe_ctlr_attr_groups,
	.release = fcoe_ctlr_device_release,
पूर्ण;

अटल स्थिर काष्ठा device_type fcoe_fcf_device_type = अणु
	.name = "fcoe_fcf",
	.groups = fcoe_fcf_attr_groups,
	.release = fcoe_fcf_device_release,
पूर्ण;

अटल sमाप_प्रकार ctlr_create_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	वापस fcoe_ctlr_create_store(bus, buf, count);
पूर्ण
अटल BUS_ATTR_WO(ctlr_create);

अटल sमाप_प्रकार ctlr_destroy_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	वापस fcoe_ctlr_destroy_store(bus, buf, count);
पूर्ण
अटल BUS_ATTR_WO(ctlr_destroy);

अटल काष्ठा attribute *fcoe_bus_attrs[] = अणु
	&bus_attr_ctlr_create.attr,
	&bus_attr_ctlr_destroy.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(fcoe_bus);

अटल काष्ठा bus_type fcoe_bus_type = अणु
	.name = "fcoe",
	.match = &fcoe_bus_match,
	.bus_groups = fcoe_bus_groups,
पूर्ण;

/**
 * fcoe_ctlr_device_flush_work() - Flush a FIP ctlr's workqueue
 * @ctlr: Poपूर्णांकer to the FIP ctlr whose workqueue is to be flushed
 */
अटल व्योम fcoe_ctlr_device_flush_work(काष्ठा fcoe_ctlr_device *ctlr)
अणु
	अगर (!fcoe_ctlr_work_q(ctlr)) अणु
		prपूर्णांकk(KERN_ERR
		       "ERROR: FIP Ctlr '%d' attempted to flush work, "
		       "when no workqueue created.\n", ctlr->id);
		dump_stack();
		वापस;
	पूर्ण

	flush_workqueue(fcoe_ctlr_work_q(ctlr));
पूर्ण

/**
 * fcoe_ctlr_device_queue_work() - Schedule work क्रम a FIP ctlr's workqueue
 * @ctlr: Poपूर्णांकer to the FIP ctlr who owns the devloss workqueue
 * @work:   Work to queue क्रम execution
 *
 * Return value:
 *	1 on success / 0 alपढ़ोy queued / < 0 क्रम error
 */
अटल पूर्णांक fcoe_ctlr_device_queue_work(काष्ठा fcoe_ctlr_device *ctlr,
				       काष्ठा work_काष्ठा *work)
अणु
	अगर (unlikely(!fcoe_ctlr_work_q(ctlr))) अणु
		prपूर्णांकk(KERN_ERR
		       "ERROR: FIP Ctlr '%d' attempted to queue work, "
		       "when no workqueue created.\n", ctlr->id);
		dump_stack();

		वापस -EINVAL;
	पूर्ण

	वापस queue_work(fcoe_ctlr_work_q(ctlr), work);
पूर्ण

/**
 * fcoe_ctlr_device_flush_devloss() - Flush a FIP ctlr's devloss workqueue
 * @ctlr: Poपूर्णांकer to FIP ctlr whose workqueue is to be flushed
 */
अटल व्योम fcoe_ctlr_device_flush_devloss(काष्ठा fcoe_ctlr_device *ctlr)
अणु
	अगर (!fcoe_ctlr_devloss_work_q(ctlr)) अणु
		prपूर्णांकk(KERN_ERR
		       "ERROR: FIP Ctlr '%d' attempted to flush work, "
		       "when no workqueue created.\n", ctlr->id);
		dump_stack();
		वापस;
	पूर्ण

	flush_workqueue(fcoe_ctlr_devloss_work_q(ctlr));
पूर्ण

/**
 * fcoe_ctlr_device_queue_devloss_work() - Schedule work क्रम a FIP ctlr's devloss workqueue
 * @ctlr: Poपूर्णांकer to the FIP ctlr who owns the devloss workqueue
 * @work:   Work to queue क्रम execution
 * @delay:  jअगरfies to delay the work queuing
 *
 * Return value:
 *	1 on success / 0 alपढ़ोy queued / < 0 क्रम error
 */
अटल पूर्णांक fcoe_ctlr_device_queue_devloss_work(काष्ठा fcoe_ctlr_device *ctlr,
					       काष्ठा delayed_work *work,
					       अचिन्हित दीर्घ delay)
अणु
	अगर (unlikely(!fcoe_ctlr_devloss_work_q(ctlr))) अणु
		prपूर्णांकk(KERN_ERR
		       "ERROR: FIP Ctlr '%d' attempted to queue work, "
		       "when no workqueue created.\n", ctlr->id);
		dump_stack();

		वापस -EINVAL;
	पूर्ण

	वापस queue_delayed_work(fcoe_ctlr_devloss_work_q(ctlr), work, delay);
पूर्ण

अटल पूर्णांक fcoe_fcf_device_match(काष्ठा fcoe_fcf_device *new,
				 काष्ठा fcoe_fcf_device *old)
अणु
	अगर (new->चयन_name == old->चयन_name &&
	    new->fabric_name == old->fabric_name &&
	    new->fc_map == old->fc_map &&
	    ether_addr_equal(new->mac, old->mac))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * fcoe_ctlr_device_add() - Add a FIP ctlr to sysfs
 * @parent:    The parent device to which the fcoe_ctlr instance
 *             should be attached
 * @f:         The LLD's FCoE sysfs function ढाँचा poपूर्णांकer
 * @priv_size: Size to be allocated with the fcoe_ctlr_device क्रम the LLD
 *
 * This routine allocates a FIP ctlr object with some additional memory
 * क्रम the LLD. The FIP ctlr is initialized, added to sysfs and then
 * attributes are added to it.
 */
काष्ठा fcoe_ctlr_device *fcoe_ctlr_device_add(काष्ठा device *parent,
				    काष्ठा fcoe_sysfs_function_ढाँचा *f,
				    पूर्णांक priv_size)
अणु
	काष्ठा fcoe_ctlr_device *ctlr;
	पूर्णांक error = 0;

	ctlr = kzalloc(माप(काष्ठा fcoe_ctlr_device) + priv_size,
		       GFP_KERNEL);
	अगर (!ctlr)
		जाओ out;

	ctlr->id = atomic_inc_वापस(&ctlr_num) - 1;
	ctlr->f = f;
	ctlr->mode = FIP_CONN_TYPE_FABRIC;
	INIT_LIST_HEAD(&ctlr->fcfs);
	mutex_init(&ctlr->lock);
	ctlr->dev.parent = parent;
	ctlr->dev.bus = &fcoe_bus_type;
	ctlr->dev.type = &fcoe_ctlr_device_type;

	ctlr->fcf_dev_loss_पंचांगo = fcoe_fcf_dev_loss_पंचांगo;

	snम_लिखो(ctlr->work_q_name, माप(ctlr->work_q_name),
		 "ctlr_wq_%d", ctlr->id);
	ctlr->work_q = create_singlethपढ़ो_workqueue(
		ctlr->work_q_name);
	अगर (!ctlr->work_q)
		जाओ out_del;

	snम_लिखो(ctlr->devloss_work_q_name,
		 माप(ctlr->devloss_work_q_name),
		 "ctlr_dl_wq_%d", ctlr->id);
	ctlr->devloss_work_q = create_singlethपढ़ो_workqueue(
		ctlr->devloss_work_q_name);
	अगर (!ctlr->devloss_work_q)
		जाओ out_del_q;

	dev_set_name(&ctlr->dev, "ctlr_%d", ctlr->id);
	error = device_रेजिस्टर(&ctlr->dev);
	अगर (error)
		जाओ out_del_q2;

	वापस ctlr;

out_del_q2:
	destroy_workqueue(ctlr->devloss_work_q);
	ctlr->devloss_work_q = शून्य;
out_del_q:
	destroy_workqueue(ctlr->work_q);
	ctlr->work_q = शून्य;
out_del:
	kमुक्त(ctlr);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_ctlr_device_add);

/**
 * fcoe_ctlr_device_delete() - Delete a FIP ctlr and its subtree from sysfs
 * @ctlr: A poपूर्णांकer to the ctlr to be deleted
 *
 * Deletes a FIP ctlr and any fcfs attached
 * to it. Deleting fcfs will cause their childen
 * to be deleted as well.
 *
 * The ctlr is detached from sysfs and it's resources
 * are मुक्तd (work q), but the memory is not मुक्तd
 * until its last reference is released.
 *
 * This routine expects no locks to be held beक्रमe
 * calling.
 *
 * TODO: Currently there are no callbacks to clean up LLD data
 * क्रम a fcoe_fcf_device. LLDs must keep this in mind as they need
 * to clean up each of their LLD data क्रम all fcoe_fcf_device beक्रमe
 * calling fcoe_ctlr_device_delete.
 */
व्योम fcoe_ctlr_device_delete(काष्ठा fcoe_ctlr_device *ctlr)
अणु
	काष्ठा fcoe_fcf_device *fcf, *next;
	/* Remove any attached fcfs */
	mutex_lock(&ctlr->lock);
	list_क्रम_each_entry_safe(fcf, next,
				 &ctlr->fcfs, peers) अणु
		list_del(&fcf->peers);
		fcf->state = FCOE_FCF_STATE_DELETED;
		fcoe_ctlr_device_queue_work(ctlr, &fcf->delete_work);
	पूर्ण
	mutex_unlock(&ctlr->lock);

	fcoe_ctlr_device_flush_work(ctlr);

	destroy_workqueue(ctlr->devloss_work_q);
	ctlr->devloss_work_q = शून्य;
	destroy_workqueue(ctlr->work_q);
	ctlr->work_q = शून्य;

	device_unरेजिस्टर(&ctlr->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_ctlr_device_delete);

/**
 * fcoe_fcf_device_final_delete() - Final delete routine
 * @work: The FIP fcf's embedded work काष्ठा
 *
 * It is expected that the fcf has been हटाओd from
 * the FIP ctlr's list beक्रमe calling this routine.
 */
अटल व्योम fcoe_fcf_device_final_delete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_fcf_device *fcf =
		container_of(work, काष्ठा fcoe_fcf_device, delete_work);
	काष्ठा fcoe_ctlr_device *ctlr = fcoe_fcf_dev_to_ctlr_dev(fcf);

	/*
	 * Cancel any outstanding समयrs. These should really exist
	 * only when rmmod'ing the LLDD and we're asking क्रम
	 * immediate termination of the rports
	 */
	अगर (!cancel_delayed_work(&fcf->dev_loss_work))
		fcoe_ctlr_device_flush_devloss(ctlr);

	device_unरेजिस्टर(&fcf->dev);
पूर्ण

/**
 * fip_समयout_deleted_fcf() - Delete a fcf when the devloss समयr fires
 * @work: The FIP fcf's embedded work काष्ठा
 *
 * Removes the fcf from the FIP ctlr's list of fcfs and
 * queues the final deletion.
 */
अटल व्योम fip_समयout_deleted_fcf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_fcf_device *fcf =
		container_of(work, काष्ठा fcoe_fcf_device, dev_loss_work.work);
	काष्ठा fcoe_ctlr_device *ctlr = fcoe_fcf_dev_to_ctlr_dev(fcf);

	mutex_lock(&ctlr->lock);

	/*
	 * If the fcf is deleted or reconnected beक्रमe the समयr
	 * fires the devloss queue will be flushed, but the state will
	 * either be CONNECTED or DELETED. If that is the हाल we
	 * cancel deleting the fcf.
	 */
	अगर (fcf->state != FCOE_FCF_STATE_DISCONNECTED)
		जाओ out;

	dev_prपूर्णांकk(KERN_ERR, &fcf->dev,
		   "FIP fcf connection time out: removing fcf\n");

	list_del(&fcf->peers);
	fcf->state = FCOE_FCF_STATE_DELETED;
	fcoe_ctlr_device_queue_work(ctlr, &fcf->delete_work);

out:
	mutex_unlock(&ctlr->lock);
पूर्ण

/**
 * fcoe_fcf_device_delete() - Delete a FIP fcf
 * @fcf: Poपूर्णांकer to the fcf which is to be deleted
 *
 * Queues the FIP fcf on the devloss workqueue
 *
 * Expects the ctlr_attrs mutex to be held क्रम fcf
 * state change.
 */
व्योम fcoe_fcf_device_delete(काष्ठा fcoe_fcf_device *fcf)
अणु
	काष्ठा fcoe_ctlr_device *ctlr = fcoe_fcf_dev_to_ctlr_dev(fcf);
	पूर्णांक समयout = fcf->dev_loss_पंचांगo;

	अगर (fcf->state != FCOE_FCF_STATE_CONNECTED)
		वापस;

	fcf->state = FCOE_FCF_STATE_DISCONNECTED;

	/*
	 * FCF will only be re-connected by the LLD calling
	 * fcoe_fcf_device_add, and it should be setting up
	 * priv then.
	 */
	fcf->priv = शून्य;

	fcoe_ctlr_device_queue_devloss_work(ctlr, &fcf->dev_loss_work,
					   समयout * HZ);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_fcf_device_delete);

/**
 * fcoe_fcf_device_add() - Add a FCoE sysfs fcoe_fcf_device to the प्रणाली
 * @ctlr:    The fcoe_ctlr_device that will be the fcoe_fcf_device parent
 * @new_fcf: A temporary FCF used क्रम lookups on the current list of fcfs
 *
 * Expects to be called with the ctlr->lock held
 */
काष्ठा fcoe_fcf_device *fcoe_fcf_device_add(काष्ठा fcoe_ctlr_device *ctlr,
					    काष्ठा fcoe_fcf_device *new_fcf)
अणु
	काष्ठा fcoe_fcf_device *fcf;
	पूर्णांक error = 0;

	list_क्रम_each_entry(fcf, &ctlr->fcfs, peers) अणु
		अगर (fcoe_fcf_device_match(new_fcf, fcf)) अणु
			अगर (fcf->state == FCOE_FCF_STATE_CONNECTED)
				वापस fcf;

			fcf->state = FCOE_FCF_STATE_CONNECTED;

			अगर (!cancel_delayed_work(&fcf->dev_loss_work))
				fcoe_ctlr_device_flush_devloss(ctlr);

			वापस fcf;
		पूर्ण
	पूर्ण

	fcf = kzalloc(माप(काष्ठा fcoe_fcf_device), GFP_ATOMIC);
	अगर (unlikely(!fcf))
		जाओ out;

	INIT_WORK(&fcf->delete_work, fcoe_fcf_device_final_delete);
	INIT_DELAYED_WORK(&fcf->dev_loss_work, fip_समयout_deleted_fcf);

	fcf->dev.parent = &ctlr->dev;
	fcf->dev.bus = &fcoe_bus_type;
	fcf->dev.type = &fcoe_fcf_device_type;
	fcf->id = atomic_inc_वापस(&fcf_num) - 1;
	fcf->state = FCOE_FCF_STATE_UNKNOWN;

	fcf->dev_loss_पंचांगo = ctlr->fcf_dev_loss_पंचांगo;

	dev_set_name(&fcf->dev, "fcf_%d", fcf->id);

	fcf->fabric_name = new_fcf->fabric_name;
	fcf->चयन_name = new_fcf->चयन_name;
	fcf->fc_map = new_fcf->fc_map;
	fcf->vfid = new_fcf->vfid;
	स_नकल(fcf->mac, new_fcf->mac, ETH_ALEN);
	fcf->priority = new_fcf->priority;
	fcf->fka_period = new_fcf->fka_period;
	fcf->selected = new_fcf->selected;

	error = device_रेजिस्टर(&fcf->dev);
	अगर (error)
		जाओ out_del;

	fcf->state = FCOE_FCF_STATE_CONNECTED;
	list_add_tail(&fcf->peers, &ctlr->fcfs);

	वापस fcf;

out_del:
	kमुक्त(fcf);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_fcf_device_add);

पूर्णांक __init fcoe_sysfs_setup(व्योम)
अणु
	atomic_set(&ctlr_num, 0);
	atomic_set(&fcf_num, 0);

	वापस bus_रेजिस्टर(&fcoe_bus_type);
पूर्ण

व्योम __निकास fcoe_sysfs_tearकरोwn(व्योम)
अणु
	bus_unरेजिस्टर(&fcoe_bus_type);
पूर्ण
