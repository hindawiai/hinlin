<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Link Layer Control manager
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#समावेश <net/nfc/llc.h>

#समावेश "llc.h"

अटल LIST_HEAD(llc_engines);

पूर्णांक nfc_llc_init(व्योम)
अणु
	पूर्णांक r;

	r = nfc_llc_nop_रेजिस्टर();
	अगर (r)
		जाओ निकास;

	r = nfc_llc_shdlc_रेजिस्टर();
	अगर (r)
		जाओ निकास;

	वापस 0;

निकास:
	nfc_llc_निकास();
	वापस r;
पूर्ण

व्योम nfc_llc_निकास(व्योम)
अणु
	काष्ठा nfc_llc_engine *llc_engine, *n;

	list_क्रम_each_entry_safe(llc_engine, n, &llc_engines, entry) अणु
		list_del(&llc_engine->entry);
		kमुक्त(llc_engine->name);
		kमुक्त(llc_engine);
	पूर्ण
पूर्ण

पूर्णांक nfc_llc_रेजिस्टर(स्थिर अक्षर *name, काष्ठा nfc_llc_ops *ops)
अणु
	काष्ठा nfc_llc_engine *llc_engine;

	llc_engine = kzalloc(माप(काष्ठा nfc_llc_engine), GFP_KERNEL);
	अगर (llc_engine == शून्य)
		वापस -ENOMEM;

	llc_engine->name = kstrdup(name, GFP_KERNEL);
	अगर (llc_engine->name == शून्य) अणु
		kमुक्त(llc_engine);
		वापस -ENOMEM;
	पूर्ण
	llc_engine->ops = ops;

	INIT_LIST_HEAD(&llc_engine->entry);
	list_add_tail(&llc_engine->entry, &llc_engines);

	वापस 0;
पूर्ण

अटल काष्ठा nfc_llc_engine *nfc_llc_name_to_engine(स्थिर अक्षर *name)
अणु
	काष्ठा nfc_llc_engine *llc_engine;

	list_क्रम_each_entry(llc_engine, &llc_engines, entry) अणु
		अगर (म_भेद(llc_engine->name, name) == 0)
			वापस llc_engine;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम nfc_llc_unरेजिस्टर(स्थिर अक्षर *name)
अणु
	काष्ठा nfc_llc_engine *llc_engine;

	llc_engine = nfc_llc_name_to_engine(name);
	अगर (llc_engine == शून्य)
		वापस;

	list_del(&llc_engine->entry);
	kमुक्त(llc_engine->name);
	kमुक्त(llc_engine);
पूर्ण

काष्ठा nfc_llc *nfc_llc_allocate(स्थिर अक्षर *name, काष्ठा nfc_hci_dev *hdev,
				 xmit_to_drv_t xmit_to_drv,
				 rcv_to_hci_t rcv_to_hci, पूर्णांक tx_headroom,
				 पूर्णांक tx_tailroom, llc_failure_t llc_failure)
अणु
	काष्ठा nfc_llc_engine *llc_engine;
	काष्ठा nfc_llc *llc;

	llc_engine = nfc_llc_name_to_engine(name);
	अगर (llc_engine == शून्य)
		वापस शून्य;

	llc = kzalloc(माप(काष्ठा nfc_llc), GFP_KERNEL);
	अगर (llc == शून्य)
		वापस शून्य;

	llc->data = llc_engine->ops->init(hdev, xmit_to_drv, rcv_to_hci,
					  tx_headroom, tx_tailroom,
					  &llc->rx_headroom, &llc->rx_tailroom,
					  llc_failure);
	अगर (llc->data == शून्य) अणु
		kमुक्त(llc);
		वापस शून्य;
	पूर्ण
	llc->ops = llc_engine->ops;

	वापस llc;
पूर्ण

व्योम nfc_llc_मुक्त(काष्ठा nfc_llc *llc)
अणु
	llc->ops->deinit(llc);
	kमुक्त(llc);
पूर्ण

पूर्णांक nfc_llc_start(काष्ठा nfc_llc *llc)
अणु
	वापस llc->ops->start(llc);
पूर्ण
EXPORT_SYMBOL(nfc_llc_start);

पूर्णांक nfc_llc_stop(काष्ठा nfc_llc *llc)
अणु
	वापस llc->ops->stop(llc);
पूर्ण
EXPORT_SYMBOL(nfc_llc_stop);

व्योम nfc_llc_rcv_from_drv(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	llc->ops->rcv_from_drv(llc, skb);
पूर्ण

पूर्णांक nfc_llc_xmit_from_hci(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	वापस llc->ops->xmit_from_hci(llc, skb);
पूर्ण

व्योम *nfc_llc_get_data(काष्ठा nfc_llc *llc)
अणु
	वापस llc->data;
पूर्ण
