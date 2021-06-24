<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_ether_configfs.h
 *
 * Utility definitions क्रम configfs support in USB Ethernet functions
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित __U_ETHER_CONFIGFS_H
#घोषणा __U_ETHER_CONFIGFS_H

#घोषणा USB_ETHERNET_CONFIGFS_ITEM(_f_)					\
	अटल व्योम _f_##_attr_release(काष्ठा config_item *item)	\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
									\
		usb_put_function_instance(&opts->func_inst);		\
	पूर्ण								\
									\
	अटल काष्ठा configfs_item_operations _f_##_item_ops = अणु	\
		.release	= _f_##_attr_release,			\
	पूर्ण

#घोषणा USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(_f_)			\
	अटल sमाप_प्रकार _f_##_opts_dev_addr_show(काष्ठा config_item *item, \
						अक्षर *page)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक result;						\
									\
		mutex_lock(&opts->lock);				\
		result = gether_get_dev_addr(opts->net, page, PAGE_SIZE); \
		mutex_unlock(&opts->lock);				\
									\
		वापस result;						\
	पूर्ण								\
									\
	अटल sमाप_प्रकार _f_##_opts_dev_addr_store(काष्ठा config_item *item, \
						 स्थिर अक्षर *page, माप_प्रकार len)\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret;						\
									\
		mutex_lock(&opts->lock);				\
		अगर (opts->refcnt) अणु					\
			mutex_unlock(&opts->lock);			\
			वापस -EBUSY;					\
		पूर्ण							\
									\
		ret = gether_set_dev_addr(opts->net, page);		\
		mutex_unlock(&opts->lock);				\
		अगर (!ret)						\
			ret = len;					\
		वापस ret;						\
	पूर्ण								\
									\
	CONFIGFS_ATTR(_f_##_opts_, dev_addr)

#घोषणा USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(_f_)			\
	अटल sमाप_प्रकार _f_##_opts_host_addr_show(काष्ठा config_item *item, \
						 अक्षर *page)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक result;						\
									\
		mutex_lock(&opts->lock);				\
		result = gether_get_host_addr(opts->net, page, PAGE_SIZE); \
		mutex_unlock(&opts->lock);				\
									\
		वापस result;						\
	पूर्ण								\
									\
	अटल sमाप_प्रकार _f_##_opts_host_addr_store(काष्ठा config_item *item, \
						  स्थिर अक्षर *page, माप_प्रकार len)\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret;						\
									\
		mutex_lock(&opts->lock);				\
		अगर (opts->refcnt) अणु					\
			mutex_unlock(&opts->lock);			\
			वापस -EBUSY;					\
		पूर्ण							\
									\
		ret = gether_set_host_addr(opts->net, page);		\
		mutex_unlock(&opts->lock);				\
		अगर (!ret)						\
			ret = len;					\
		वापस ret;						\
	पूर्ण								\
									\
	CONFIGFS_ATTR(_f_##_opts_, host_addr)

#घोषणा USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(_f_)			\
	अटल sमाप_प्रकार _f_##_opts_qmult_show(काष्ठा config_item *item,	\
					     अक्षर *page)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		अचिन्हित qmult;						\
									\
		mutex_lock(&opts->lock);				\
		qmult = gether_get_qmult(opts->net);			\
		mutex_unlock(&opts->lock);				\
		वापस प्र_लिखो(page, "%d\n", qmult);			\
	पूर्ण								\
									\
	अटल sमाप_प्रकार _f_##_opts_qmult_store(काष्ठा config_item *item, \
					      स्थिर अक्षर *page, माप_प्रकार len)\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		u8 val;							\
		पूर्णांक ret;						\
									\
		mutex_lock(&opts->lock);				\
		अगर (opts->refcnt) अणु					\
			ret = -EBUSY;					\
			जाओ out;					\
		पूर्ण							\
									\
		ret = kstrtou8(page, 0, &val);				\
		अगर (ret)						\
			जाओ out;					\
									\
		gether_set_qmult(opts->net, val);			\
		ret = len;						\
out:									\
		mutex_unlock(&opts->lock);				\
		वापस ret;						\
	पूर्ण								\
									\
	CONFIGFS_ATTR(_f_##_opts_, qmult)

#घोषणा USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(_f_)			\
	अटल sमाप_प्रकार _f_##_opts_अगरname_show(काष्ठा config_item *item, \
					      अक्षर *page)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret;						\
									\
		mutex_lock(&opts->lock);				\
		ret = gether_get_अगरname(opts->net, page, PAGE_SIZE);	\
		mutex_unlock(&opts->lock);				\
									\
		वापस ret;						\
	पूर्ण								\
									\
	अटल sमाप_प्रकार _f_##_opts_अगरname_store(काष्ठा config_item *item, \
					       स्थिर अक्षर *page, माप_प्रकार len)\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret = -EBUSY;					\
									\
		mutex_lock(&opts->lock);				\
		अगर (!opts->refcnt)					\
			ret = gether_set_अगरname(opts->net, page, len);	\
		mutex_unlock(&opts->lock);				\
		वापस ret ?: len;					\
	पूर्ण								\
									\
	CONFIGFS_ATTR(_f_##_opts_, अगरname)

#घोषणा USB_ETHER_CONFIGFS_ITEM_ATTR_U8_RW(_f_, _n_)			\
	अटल sमाप_प्रकार _f_##_opts_##_n_##_show(काष्ठा config_item *item,\
					       अक्षर *page)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret;						\
									\
		mutex_lock(&opts->lock);				\
		ret = प्र_लिखो(page, "%02x\n", opts->_n_);		\
		mutex_unlock(&opts->lock);				\
									\
		वापस ret;						\
	पूर्ण								\
									\
	अटल sमाप_प्रकार _f_##_opts_##_n_##_store(काष्ठा config_item *item,\
						स्थिर अक्षर *page,	\
						माप_प्रकार len)		\
	अणु								\
		काष्ठा f_##_f_##_opts *opts = to_f_##_f_##_opts(item);	\
		पूर्णांक ret = -EINVAL;					\
		u8 val;							\
									\
		mutex_lock(&opts->lock);				\
		अगर (माला_पूछो(page, "%02hhx", &val) > 0) अणु			\
			opts->_n_ = val;				\
			ret = len;					\
		पूर्ण							\
		mutex_unlock(&opts->lock);				\
									\
		वापस ret;						\
	पूर्ण								\
									\
	CONFIGFS_ATTR(_f_##_opts_, _n_)

#पूर्ण_अगर /* __U_ETHER_CONFIGFS_H */
