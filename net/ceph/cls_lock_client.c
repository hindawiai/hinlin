<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/cls_lock_client.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/libceph.h>

/**
 * ceph_cls_lock - grab raकरोs lock क्रम object
 * @oid, @oloc: object to lock
 * @lock_name: the name of the lock
 * @type: lock type (CEPH_CLS_LOCK_EXCLUSIVE or CEPH_CLS_LOCK_SHARED)
 * @cookie: user-defined identअगरier क्रम this instance of the lock
 * @tag: user-defined tag
 * @desc: user-defined lock description
 * @flags: lock flags
 *
 * All operations on the same lock should use the same tag.
 */
पूर्णांक ceph_cls_lock(काष्ठा ceph_osd_client *osdc,
		  काष्ठा ceph_object_id *oid,
		  काष्ठा ceph_object_locator *oloc,
		  अक्षर *lock_name, u8 type, अक्षर *cookie,
		  अक्षर *tag, अक्षर *desc, u8 flags)
अणु
	पूर्णांक lock_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	पूर्णांक cookie_len = म_माप(cookie);
	पूर्णांक tag_len = म_माप(tag);
	पूर्णांक desc_len = म_माप(desc);
	व्योम *p, *end;
	काष्ठा page *lock_op_page;
	काष्ठा बारpec64 mसमय;
	पूर्णांक ret;

	lock_op_buf_size = name_len + माप(__le32) +
			   cookie_len + माप(__le32) +
			   tag_len + माप(__le32) +
			   desc_len + माप(__le32) +
			   माप(काष्ठा ceph_बारpec) +
			   /* flag and type */
			   माप(u8) + माप(u8) +
			   CEPH_ENCODING_START_BLK_LEN;
	अगर (lock_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	lock_op_page = alloc_page(GFP_NOIO);
	अगर (!lock_op_page)
		वापस -ENOMEM;

	p = page_address(lock_op_page);
	end = p + lock_op_buf_size;

	/* encode cls_lock_lock_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    lock_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);
	ceph_encode_8(&p, type);
	ceph_encode_string(&p, end, cookie, cookie_len);
	ceph_encode_string(&p, end, tag, tag_len);
	ceph_encode_string(&p, end, desc, desc_len);
	/* only support infinite duration */
	स_रखो(&mसमय, 0, माप(mसमय));
	ceph_encode_बारpec64(p, &mसमय);
	p += माप(काष्ठा ceph_बारpec);
	ceph_encode_8(&p, flags);

	करोut("%s lock_name %s type %d cookie %s tag %s desc %s flags 0x%x\n",
	     __func__, lock_name, type, cookie, tag, desc, flags);
	ret = ceph_osdc_call(osdc, oid, oloc, "lock", "lock",
			     CEPH_OSD_FLAG_WRITE, lock_op_page,
			     lock_op_buf_size, शून्य, शून्य);

	करोut("%s: status %d\n", __func__, ret);
	__मुक्त_page(lock_op_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_cls_lock);

/**
 * ceph_cls_unlock - release raकरोs lock क्रम object
 * @oid, @oloc: object to lock
 * @lock_name: the name of the lock
 * @cookie: user-defined identअगरier क्रम this instance of the lock
 */
पूर्णांक ceph_cls_unlock(काष्ठा ceph_osd_client *osdc,
		    काष्ठा ceph_object_id *oid,
		    काष्ठा ceph_object_locator *oloc,
		    अक्षर *lock_name, अक्षर *cookie)
अणु
	पूर्णांक unlock_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	पूर्णांक cookie_len = म_माप(cookie);
	व्योम *p, *end;
	काष्ठा page *unlock_op_page;
	पूर्णांक ret;

	unlock_op_buf_size = name_len + माप(__le32) +
			     cookie_len + माप(__le32) +
			     CEPH_ENCODING_START_BLK_LEN;
	अगर (unlock_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	unlock_op_page = alloc_page(GFP_NOIO);
	अगर (!unlock_op_page)
		वापस -ENOMEM;

	p = page_address(unlock_op_page);
	end = p + unlock_op_buf_size;

	/* encode cls_lock_unlock_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    unlock_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);
	ceph_encode_string(&p, end, cookie, cookie_len);

	करोut("%s lock_name %s cookie %s\n", __func__, lock_name, cookie);
	ret = ceph_osdc_call(osdc, oid, oloc, "lock", "unlock",
			     CEPH_OSD_FLAG_WRITE, unlock_op_page,
			     unlock_op_buf_size, शून्य, शून्य);

	करोut("%s: status %d\n", __func__, ret);
	__मुक्त_page(unlock_op_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_cls_unlock);

/**
 * ceph_cls_अवरोध_lock - release raकरोs lock क्रम object क्रम specअगरied client
 * @oid, @oloc: object to lock
 * @lock_name: the name of the lock
 * @cookie: user-defined identअगरier क्रम this instance of the lock
 * @locker: current lock owner
 */
पूर्णांक ceph_cls_अवरोध_lock(काष्ठा ceph_osd_client *osdc,
			काष्ठा ceph_object_id *oid,
			काष्ठा ceph_object_locator *oloc,
			अक्षर *lock_name, अक्षर *cookie,
			काष्ठा ceph_entity_name *locker)
अणु
	पूर्णांक अवरोध_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	पूर्णांक cookie_len = म_माप(cookie);
	काष्ठा page *अवरोध_op_page;
	व्योम *p, *end;
	पूर्णांक ret;

	अवरोध_op_buf_size = name_len + माप(__le32) +
			    cookie_len + माप(__le32) +
			    माप(u8) + माप(__le64) +
			    CEPH_ENCODING_START_BLK_LEN;
	अगर (अवरोध_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	अवरोध_op_page = alloc_page(GFP_NOIO);
	अगर (!अवरोध_op_page)
		वापस -ENOMEM;

	p = page_address(अवरोध_op_page);
	end = p + अवरोध_op_buf_size;

	/* encode cls_lock_अवरोध_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    अवरोध_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);
	ceph_encode_copy(&p, locker, माप(*locker));
	ceph_encode_string(&p, end, cookie, cookie_len);

	करोut("%s lock_name %s cookie %s locker %s%llu\n", __func__, lock_name,
	     cookie, ENTITY_NAME(*locker));
	ret = ceph_osdc_call(osdc, oid, oloc, "lock", "break_lock",
			     CEPH_OSD_FLAG_WRITE, अवरोध_op_page,
			     अवरोध_op_buf_size, शून्य, शून्य);

	करोut("%s: status %d\n", __func__, ret);
	__मुक्त_page(अवरोध_op_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_cls_अवरोध_lock);

पूर्णांक ceph_cls_set_cookie(काष्ठा ceph_osd_client *osdc,
			काष्ठा ceph_object_id *oid,
			काष्ठा ceph_object_locator *oloc,
			अक्षर *lock_name, u8 type, अक्षर *old_cookie,
			अक्षर *tag, अक्षर *new_cookie)
अणु
	पूर्णांक cookie_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	पूर्णांक old_cookie_len = म_माप(old_cookie);
	पूर्णांक tag_len = म_माप(tag);
	पूर्णांक new_cookie_len = म_माप(new_cookie);
	व्योम *p, *end;
	काष्ठा page *cookie_op_page;
	पूर्णांक ret;

	cookie_op_buf_size = name_len + माप(__le32) +
			     old_cookie_len + माप(__le32) +
			     tag_len + माप(__le32) +
			     new_cookie_len + माप(__le32) +
			     माप(u8) + CEPH_ENCODING_START_BLK_LEN;
	अगर (cookie_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	cookie_op_page = alloc_page(GFP_NOIO);
	अगर (!cookie_op_page)
		वापस -ENOMEM;

	p = page_address(cookie_op_page);
	end = p + cookie_op_buf_size;

	/* encode cls_lock_set_cookie_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    cookie_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);
	ceph_encode_8(&p, type);
	ceph_encode_string(&p, end, old_cookie, old_cookie_len);
	ceph_encode_string(&p, end, tag, tag_len);
	ceph_encode_string(&p, end, new_cookie, new_cookie_len);

	करोut("%s lock_name %s type %d old_cookie %s tag %s new_cookie %s\n",
	     __func__, lock_name, type, old_cookie, tag, new_cookie);
	ret = ceph_osdc_call(osdc, oid, oloc, "lock", "set_cookie",
			     CEPH_OSD_FLAG_WRITE, cookie_op_page,
			     cookie_op_buf_size, शून्य, शून्य);

	करोut("%s: status %d\n", __func__, ret);
	__मुक्त_page(cookie_op_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_cls_set_cookie);

व्योम ceph_मुक्त_lockers(काष्ठा ceph_locker *lockers, u32 num_lockers)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_lockers; i++)
		kमुक्त(lockers[i].id.cookie);
	kमुक्त(lockers);
पूर्ण
EXPORT_SYMBOL(ceph_मुक्त_lockers);

अटल पूर्णांक decode_locker(व्योम **p, व्योम *end, काष्ठा ceph_locker *locker)
अणु
	u8 काष्ठा_v;
	u32 len;
	अक्षर *s;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 1, "locker_id_t", &काष्ठा_v, &len);
	अगर (ret)
		वापस ret;

	ceph_decode_copy(p, &locker->id.name, माप(locker->id.name));
	s = ceph_extract_encoded_string(p, end, शून्य, GFP_NOIO);
	अगर (IS_ERR(s))
		वापस PTR_ERR(s);

	locker->id.cookie = s;

	ret = ceph_start_decoding(p, end, 1, "locker_info_t", &काष्ठा_v, &len);
	अगर (ret)
		वापस ret;

	*p += माप(काष्ठा ceph_बारpec); /* skip expiration */

	ret = ceph_decode_entity_addr(p, end, &locker->info.addr);
	अगर (ret)
		वापस ret;

	len = ceph_decode_32(p);
	*p += len; /* skip description */

	करोut("%s %s%llu cookie %s addr %s\n", __func__,
	     ENTITY_NAME(locker->id.name), locker->id.cookie,
	     ceph_pr_addr(&locker->info.addr));
	वापस 0;
पूर्ण

अटल पूर्णांक decode_lockers(व्योम **p, व्योम *end, u8 *type, अक्षर **tag,
			  काष्ठा ceph_locker **lockers, u32 *num_lockers)
अणु
	u8 काष्ठा_v;
	u32 काष्ठा_len;
	अक्षर *s;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 1, "cls_lock_get_info_reply",
				  &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		वापस ret;

	*num_lockers = ceph_decode_32(p);
	*lockers = kसुस्मृति(*num_lockers, माप(**lockers), GFP_NOIO);
	अगर (!*lockers)
		वापस -ENOMEM;

	क्रम (i = 0; i < *num_lockers; i++) अणु
		ret = decode_locker(p, end, *lockers + i);
		अगर (ret)
			जाओ err_मुक्त_lockers;
	पूर्ण

	*type = ceph_decode_8(p);
	s = ceph_extract_encoded_string(p, end, शून्य, GFP_NOIO);
	अगर (IS_ERR(s)) अणु
		ret = PTR_ERR(s);
		जाओ err_मुक्त_lockers;
	पूर्ण

	*tag = s;
	वापस 0;

err_मुक्त_lockers:
	ceph_मुक्त_lockers(*lockers, *num_lockers);
	वापस ret;
पूर्ण

/*
 * On success, the caller is responsible क्रम:
 *
 *     kमुक्त(tag);
 *     ceph_मुक्त_lockers(lockers, num_lockers);
 */
पूर्णांक ceph_cls_lock_info(काष्ठा ceph_osd_client *osdc,
		       काष्ठा ceph_object_id *oid,
		       काष्ठा ceph_object_locator *oloc,
		       अक्षर *lock_name, u8 *type, अक्षर **tag,
		       काष्ठा ceph_locker **lockers, u32 *num_lockers)
अणु
	पूर्णांक get_info_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	काष्ठा page *get_info_op_page, *reply_page;
	माप_प्रकार reply_len = PAGE_SIZE;
	व्योम *p, *end;
	पूर्णांक ret;

	get_info_op_buf_size = name_len + माप(__le32) +
			       CEPH_ENCODING_START_BLK_LEN;
	अगर (get_info_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	get_info_op_page = alloc_page(GFP_NOIO);
	अगर (!get_info_op_page)
		वापस -ENOMEM;

	reply_page = alloc_page(GFP_NOIO);
	अगर (!reply_page) अणु
		__मुक्त_page(get_info_op_page);
		वापस -ENOMEM;
	पूर्ण

	p = page_address(get_info_op_page);
	end = p + get_info_op_buf_size;

	/* encode cls_lock_get_info_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    get_info_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);

	करोut("%s lock_name %s\n", __func__, lock_name);
	ret = ceph_osdc_call(osdc, oid, oloc, "lock", "get_info",
			     CEPH_OSD_FLAG_READ, get_info_op_page,
			     get_info_op_buf_size, &reply_page, &reply_len);

	करोut("%s: status %d\n", __func__, ret);
	अगर (ret >= 0) अणु
		p = page_address(reply_page);
		end = p + reply_len;

		ret = decode_lockers(&p, end, type, tag, lockers, num_lockers);
	पूर्ण

	__मुक्त_page(get_info_op_page);
	__मुक्त_page(reply_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_cls_lock_info);

पूर्णांक ceph_cls_निश्चित_locked(काष्ठा ceph_osd_request *req, पूर्णांक which,
			   अक्षर *lock_name, u8 type, अक्षर *cookie, अक्षर *tag)
अणु
	पूर्णांक निश्चित_op_buf_size;
	पूर्णांक name_len = म_माप(lock_name);
	पूर्णांक cookie_len = म_माप(cookie);
	पूर्णांक tag_len = म_माप(tag);
	काष्ठा page **pages;
	व्योम *p, *end;
	पूर्णांक ret;

	निश्चित_op_buf_size = name_len + माप(__le32) +
			     cookie_len + माप(__le32) +
			     tag_len + माप(__le32) +
			     माप(u8) + CEPH_ENCODING_START_BLK_LEN;
	अगर (निश्चित_op_buf_size > PAGE_SIZE)
		वापस -E2BIG;

	ret = osd_req_op_cls_init(req, which, "lock", "assert_locked");
	अगर (ret)
		वापस ret;

	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	p = page_address(pages[0]);
	end = p + निश्चित_op_buf_size;

	/* encode cls_lock_निश्चित_op काष्ठा */
	ceph_start_encoding(&p, 1, 1,
			    निश्चित_op_buf_size - CEPH_ENCODING_START_BLK_LEN);
	ceph_encode_string(&p, end, lock_name, name_len);
	ceph_encode_8(&p, type);
	ceph_encode_string(&p, end, cookie, cookie_len);
	ceph_encode_string(&p, end, tag, tag_len);
	WARN_ON(p != end);

	osd_req_op_cls_request_data_pages(req, which, pages, निश्चित_op_buf_size,
					  0, false, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_cls_निश्चित_locked);
