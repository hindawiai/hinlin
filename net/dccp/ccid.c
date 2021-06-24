<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/ccid.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 *  CCID infraकाष्ठाure
 */

#समावेश <linux/slab.h>

#समावेश "ccid.h"
#समावेश "ccids/lib/tfrc.h"

अटल काष्ठा ccid_operations *ccids[] = अणु
	&ccid2_ops,
#अगर_घोषित CONFIG_IP_DCCP_CCID3
	&ccid3_ops,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा ccid_operations *ccid_by_number(स्थिर u8 id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ccids); i++)
		अगर (ccids[i]->ccid_id == id)
			वापस ccids[i];
	वापस शून्य;
पूर्ण

/* check that up to @array_len members in @ccid_array are supported */
bool ccid_support_check(u8 स्थिर *ccid_array, u8 array_len)
अणु
	जबतक (array_len > 0)
		अगर (ccid_by_number(ccid_array[--array_len]) == शून्य)
			वापस false;
	वापस true;
पूर्ण

/**
 * ccid_get_builtin_ccids  -  Populate a list of built-in CCIDs
 * @ccid_array: poपूर्णांकer to copy पूर्णांकo
 * @array_len: value to वापस length पूर्णांकo
 *
 * This function allocates memory - caller must see that it is मुक्तd after use.
 */
पूर्णांक ccid_get_builtin_ccids(u8 **ccid_array, u8 *array_len)
अणु
	*ccid_array = kदो_स्मृति(ARRAY_SIZE(ccids), gfp_any());
	अगर (*ccid_array == शून्य)
		वापस -ENOBUFS;

	क्रम (*array_len = 0; *array_len < ARRAY_SIZE(ccids); *array_len += 1)
		(*ccid_array)[*array_len] = ccids[*array_len]->ccid_id;
	वापस 0;
पूर्ण

पूर्णांक ccid_माला_लोockopt_builtin_ccids(काष्ठा sock *sk, पूर्णांक len,
				  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	u8 *ccid_array, array_len;
	पूर्णांक err = 0;

	अगर (ccid_get_builtin_ccids(&ccid_array, &array_len))
		वापस -ENOBUFS;

	अगर (put_user(array_len, optlen))
		err = -EFAULT;
	अन्यथा अगर (len > 0 && copy_to_user(optval, ccid_array,
					 len > array_len ? array_len : len))
		err = -EFAULT;

	kमुक्त(ccid_array);
	वापस err;
पूर्ण

अटल __म_लिखो(3, 4) काष्ठा kmem_cache *ccid_kmem_cache_create(पूर्णांक obj_size, अक्षर *slab_name_fmt, स्थिर अक्षर *fmt,...)
अणु
	काष्ठा kmem_cache *slab;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(slab_name_fmt, CCID_SLAB_NAME_LENGTH, fmt, args);
	बहु_पूर्ण(args);

	slab = kmem_cache_create(slab_name_fmt, माप(काष्ठा ccid) + obj_size, 0,
				 SLAB_HWCACHE_ALIGN, शून्य);
	वापस slab;
पूर्ण

अटल व्योम ccid_kmem_cache_destroy(काष्ठा kmem_cache *slab)
अणु
	kmem_cache_destroy(slab);
पूर्ण

अटल पूर्णांक __init ccid_activate(काष्ठा ccid_operations *ccid_ops)
अणु
	पूर्णांक err = -ENOBUFS;

	ccid_ops->ccid_hc_rx_slab =
			ccid_kmem_cache_create(ccid_ops->ccid_hc_rx_obj_size,
					       ccid_ops->ccid_hc_rx_slab_name,
					       "ccid%u_hc_rx_sock",
					       ccid_ops->ccid_id);
	अगर (ccid_ops->ccid_hc_rx_slab == शून्य)
		जाओ out;

	ccid_ops->ccid_hc_tx_slab =
			ccid_kmem_cache_create(ccid_ops->ccid_hc_tx_obj_size,
					       ccid_ops->ccid_hc_tx_slab_name,
					       "ccid%u_hc_tx_sock",
					       ccid_ops->ccid_id);
	अगर (ccid_ops->ccid_hc_tx_slab == शून्य)
		जाओ out_मुक्त_rx_slab;

	pr_info("DCCP: Activated CCID %d (%s)\n",
		ccid_ops->ccid_id, ccid_ops->ccid_name);
	err = 0;
out:
	वापस err;
out_मुक्त_rx_slab:
	ccid_kmem_cache_destroy(ccid_ops->ccid_hc_rx_slab);
	ccid_ops->ccid_hc_rx_slab = शून्य;
	जाओ out;
पूर्ण

अटल व्योम ccid_deactivate(काष्ठा ccid_operations *ccid_ops)
अणु
	ccid_kmem_cache_destroy(ccid_ops->ccid_hc_tx_slab);
	ccid_ops->ccid_hc_tx_slab = शून्य;
	ccid_kmem_cache_destroy(ccid_ops->ccid_hc_rx_slab);
	ccid_ops->ccid_hc_rx_slab = शून्य;

	pr_info("DCCP: Deactivated CCID %d (%s)\n",
		ccid_ops->ccid_id, ccid_ops->ccid_name);
पूर्ण

काष्ठा ccid *ccid_new(स्थिर u8 id, काष्ठा sock *sk, bool rx)
अणु
	काष्ठा ccid_operations *ccid_ops = ccid_by_number(id);
	काष्ठा ccid *ccid = शून्य;

	अगर (ccid_ops == शून्य)
		जाओ out;

	ccid = kmem_cache_alloc(rx ? ccid_ops->ccid_hc_rx_slab :
				     ccid_ops->ccid_hc_tx_slab, gfp_any());
	अगर (ccid == शून्य)
		जाओ out;
	ccid->ccid_ops = ccid_ops;
	अगर (rx) अणु
		स_रखो(ccid + 1, 0, ccid_ops->ccid_hc_rx_obj_size);
		अगर (ccid->ccid_ops->ccid_hc_rx_init != शून्य &&
		    ccid->ccid_ops->ccid_hc_rx_init(ccid, sk) != 0)
			जाओ out_मुक्त_ccid;
	पूर्ण अन्यथा अणु
		स_रखो(ccid + 1, 0, ccid_ops->ccid_hc_tx_obj_size);
		अगर (ccid->ccid_ops->ccid_hc_tx_init != शून्य &&
		    ccid->ccid_ops->ccid_hc_tx_init(ccid, sk) != 0)
			जाओ out_मुक्त_ccid;
	पूर्ण
out:
	वापस ccid;
out_मुक्त_ccid:
	kmem_cache_मुक्त(rx ? ccid_ops->ccid_hc_rx_slab :
			ccid_ops->ccid_hc_tx_slab, ccid);
	ccid = शून्य;
	जाओ out;
पूर्ण

व्योम ccid_hc_rx_delete(काष्ठा ccid *ccid, काष्ठा sock *sk)
अणु
	अगर (ccid != शून्य) अणु
		अगर (ccid->ccid_ops->ccid_hc_rx_निकास != शून्य)
			ccid->ccid_ops->ccid_hc_rx_निकास(sk);
		kmem_cache_मुक्त(ccid->ccid_ops->ccid_hc_rx_slab, ccid);
	पूर्ण
पूर्ण

व्योम ccid_hc_tx_delete(काष्ठा ccid *ccid, काष्ठा sock *sk)
अणु
	अगर (ccid != शून्य) अणु
		अगर (ccid->ccid_ops->ccid_hc_tx_निकास != शून्य)
			ccid->ccid_ops->ccid_hc_tx_निकास(sk);
		kmem_cache_मुक्त(ccid->ccid_ops->ccid_hc_tx_slab, ccid);
	पूर्ण
पूर्ण

पूर्णांक __init ccid_initialize_builtins(व्योम)
अणु
	पूर्णांक i, err = tfrc_lib_init();

	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(ccids); i++) अणु
		err = ccid_activate(ccids[i]);
		अगर (err)
			जाओ unwind_registrations;
	पूर्ण
	वापस 0;

unwind_registrations:
	जबतक(--i >= 0)
		ccid_deactivate(ccids[i]);
	tfrc_lib_निकास();
	वापस err;
पूर्ण

व्योम ccid_cleanup_builtins(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ccids); i++)
		ccid_deactivate(ccids[i]);
	tfrc_lib_निकास();
पूर्ण
