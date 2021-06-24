<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_tcm.h
 *
 * Utility definitions क्रम the tcm function
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzej.p@xxxxxxxxxxx>
 */

#अगर_अघोषित U_TCM_H
#घोषणा U_TCM_H

#समावेश <linux/usb/composite.h>

/**
 * @dependent: optional dependent module. Meant क्रम legacy gadget.
 * If non-null its refcount will be increased when a tpg is created and
 * decreased when tpg is dropped.
 * @dep_lock: lock क्रम dependent module operations.
 * @पढ़ोy: true अगर the dependent module inक्रमmation is set.
 * @can_attach: true a function can be bound to gadget
 * @has_dep: true अगर there is a dependent module
 *
 */
काष्ठा f_tcm_opts अणु
	काष्ठा usb_function_instance	func_inst;
	काष्ठा module			*dependent;
	काष्ठा mutex			dep_lock;
	bool				पढ़ोy;
	bool				can_attach;
	bool				has_dep;

	/*
	 * Callbacks to be हटाओd when legacy tcm gadget disappears.
	 *
	 * If you use the new function registration पूर्णांकerface
	 * programmatically, you MUST set these callbacks to
	 * something sensible (e.g. probe/हटाओ the composite).
	 */
	पूर्णांक (*tcm_रेजिस्टर_callback)(काष्ठा usb_function_instance *);
	व्योम (*tcm_unरेजिस्टर_callback)(काष्ठा usb_function_instance *);
पूर्ण;

#पूर्ण_अगर /* U_TCM_H */
