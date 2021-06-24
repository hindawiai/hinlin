<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_resource.c
 * Author: Jakub Kicinski <jakub.kicinski@netronome.com>
 *         Jason McMullan <jason.mcmullan@netronome.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "crc32.h"
#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp6000/nfp6000.h"

#घोषणा NFP_RESOURCE_TBL_TARGET		NFP_CPP_TARGET_MU
#घोषणा NFP_RESOURCE_TBL_BASE		0x8100000000ULL

/* NFP Resource Table self-identअगरier */
#घोषणा NFP_RESOURCE_TBL_NAME		"nfp.res"
#घोषणा NFP_RESOURCE_TBL_KEY		0x00000000 /* Special key क्रम entry 0 */

#घोषणा NFP_RESOURCE_ENTRY_NAME_SZ	8

/**
 * काष्ठा nfp_resource_entry - Resource table entry
 * @mutex:	NFP CPP Lock
 * @mutex.owner:	NFP CPP Lock, पूर्णांकerface owner
 * @mutex.key:		NFP CPP Lock, posix_crc32(name, 8)
 * @region:	Memory region descriptor
 * @region.name:	ASCII, zero padded name
 * @region.reserved:	padding
 * @region.cpp_action:	CPP Action
 * @region.cpp_token:	CPP Token
 * @region.cpp_target:	CPP Target ID
 * @region.page_offset:	256-byte page offset पूर्णांकo target's CPP address
 * @region.page_size:	size, in 256-byte pages
 */
काष्ठा nfp_resource_entry अणु
	काष्ठा nfp_resource_entry_mutex अणु
		u32 owner;
		u32 key;
	पूर्ण mutex;
	काष्ठा nfp_resource_entry_region अणु
		u8  name[NFP_RESOURCE_ENTRY_NAME_SZ];
		u8  reserved[5];
		u8  cpp_action;
		u8  cpp_token;
		u8  cpp_target;
		u32 page_offset;
		u32 page_size;
	पूर्ण region;
पूर्ण;

#घोषणा NFP_RESOURCE_TBL_SIZE		4096
#घोषणा NFP_RESOURCE_TBL_ENTRIES	(NFP_RESOURCE_TBL_SIZE /	\
					 माप(काष्ठा nfp_resource_entry))

काष्ठा nfp_resource अणु
	अक्षर name[NFP_RESOURCE_ENTRY_NAME_SZ + 1];
	u32 cpp_id;
	u64 addr;
	u64 size;
	काष्ठा nfp_cpp_mutex *mutex;
पूर्ण;

अटल पूर्णांक nfp_cpp_resource_find(काष्ठा nfp_cpp *cpp, काष्ठा nfp_resource *res)
अणु
	काष्ठा nfp_resource_entry entry;
	u32 cpp_id, key;
	पूर्णांक ret, i;

	cpp_id = NFP_CPP_ID(NFP_RESOURCE_TBL_TARGET, 3, 0);  /* Atomic पढ़ो */

	/* Search क्रम a matching entry */
	अगर (!म_भेद(res->name, NFP_RESOURCE_TBL_NAME)) अणु
		nfp_err(cpp, "Grabbing device lock not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	key = crc32_posix(res->name, NFP_RESOURCE_ENTRY_NAME_SZ);

	क्रम (i = 0; i < NFP_RESOURCE_TBL_ENTRIES; i++) अणु
		u64 addr = NFP_RESOURCE_TBL_BASE +
			माप(काष्ठा nfp_resource_entry) * i;

		ret = nfp_cpp_पढ़ो(cpp, cpp_id, addr, &entry, माप(entry));
		अगर (ret != माप(entry))
			वापस -EIO;

		अगर (entry.mutex.key != key)
			जारी;

		/* Found key! */
		res->mutex =
			nfp_cpp_mutex_alloc(cpp,
					    NFP_RESOURCE_TBL_TARGET, addr, key);
		res->cpp_id = NFP_CPP_ID(entry.region.cpp_target,
					 entry.region.cpp_action,
					 entry.region.cpp_token);
		res->addr = (u64)entry.region.page_offset << 8;
		res->size = (u64)entry.region.page_size << 8;

		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
nfp_resource_try_acquire(काष्ठा nfp_cpp *cpp, काष्ठा nfp_resource *res,
			 काष्ठा nfp_cpp_mutex *dev_mutex)
अणु
	पूर्णांक err;

	अगर (nfp_cpp_mutex_lock(dev_mutex))
		वापस -EINVAL;

	err = nfp_cpp_resource_find(cpp, res);
	अगर (err)
		जाओ err_unlock_dev;

	err = nfp_cpp_mutex_trylock(res->mutex);
	अगर (err)
		जाओ err_res_mutex_मुक्त;

	nfp_cpp_mutex_unlock(dev_mutex);

	वापस 0;

err_res_mutex_मुक्त:
	nfp_cpp_mutex_मुक्त(res->mutex);
err_unlock_dev:
	nfp_cpp_mutex_unlock(dev_mutex);

	वापस err;
पूर्ण

/**
 * nfp_resource_acquire() - Acquire a resource handle
 * @cpp:	NFP CPP handle
 * @name:	Name of the resource
 *
 * NOTE: This function locks the acquired resource
 *
 * Return: NFP Resource handle, or ERR_PTR()
 */
काष्ठा nfp_resource *
nfp_resource_acquire(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ warn_at = jअगरfies + NFP_MUTEX_WAIT_FIRST_WARN * HZ;
	अचिन्हित दीर्घ err_at = jअगरfies + NFP_MUTEX_WAIT_ERROR * HZ;
	काष्ठा nfp_cpp_mutex *dev_mutex;
	काष्ठा nfp_resource *res;
	पूर्णांक err;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस ERR_PTR(-ENOMEM);

	म_नकलन(res->name, name, NFP_RESOURCE_ENTRY_NAME_SZ);

	dev_mutex = nfp_cpp_mutex_alloc(cpp, NFP_RESOURCE_TBL_TARGET,
					NFP_RESOURCE_TBL_BASE,
					NFP_RESOURCE_TBL_KEY);
	अगर (!dev_mutex) अणु
		kमुक्त(res);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (;;) अणु
		err = nfp_resource_try_acquire(cpp, res, dev_mutex);
		अगर (!err)
			अवरोध;
		अगर (err != -EBUSY)
			जाओ err_मुक्त;

		err = msleep_पूर्णांकerruptible(1);
		अगर (err != 0) अणु
			err = -ERESTARTSYS;
			जाओ err_मुक्त;
		पूर्ण

		अगर (समय_is_beक्रमe_eq_jअगरfies(warn_at)) अणु
			warn_at = jअगरfies + NFP_MUTEX_WAIT_NEXT_WARN * HZ;
			nfp_warn(cpp, "Warning: waiting for NFP resource %s\n",
				 name);
		पूर्ण
		अगर (समय_is_beक्रमe_eq_jअगरfies(err_at)) अणु
			nfp_err(cpp, "Error: resource %s timed out\n", name);
			err = -EBUSY;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	nfp_cpp_mutex_मुक्त(dev_mutex);

	वापस res;

err_मुक्त:
	nfp_cpp_mutex_मुक्त(dev_mutex);
	kमुक्त(res);
	वापस ERR_PTR(err);
पूर्ण

/**
 * nfp_resource_release() - Release a NFP Resource handle
 * @res:	NFP Resource handle
 *
 * NOTE: This function implictly unlocks the resource handle
 */
व्योम nfp_resource_release(काष्ठा nfp_resource *res)
अणु
	nfp_cpp_mutex_unlock(res->mutex);
	nfp_cpp_mutex_मुक्त(res->mutex);
	kमुक्त(res);
पूर्ण

/**
 * nfp_resource_रुको() - Wait क्रम resource to appear
 * @cpp:	NFP CPP handle
 * @name:	Name of the resource
 * @secs:	Number of seconds to रुको
 *
 * Wait क्रम resource to appear in the resource table, grab and release
 * its lock.  The रुको is jअगरfies-based, करोn't expect fine granularity.
 *
 * Return: 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक nfp_resource_रुको(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, अचिन्हित पूर्णांक secs)
अणु
	अचिन्हित दीर्घ warn_at = jअगरfies + NFP_MUTEX_WAIT_FIRST_WARN * HZ;
	अचिन्हित दीर्घ err_at = jअगरfies + secs * HZ;
	काष्ठा nfp_resource *res;

	जबतक (true) अणु
		res = nfp_resource_acquire(cpp, name);
		अगर (!IS_ERR(res)) अणु
			nfp_resource_release(res);
			वापस 0;
		पूर्ण

		अगर (PTR_ERR(res) != -ENOENT) अणु
			nfp_err(cpp, "error waiting for resource %s: %ld\n",
				name, PTR_ERR(res));
			वापस PTR_ERR(res);
		पूर्ण
		अगर (समय_is_beक्रमe_eq_jअगरfies(err_at)) अणु
			nfp_err(cpp, "timeout waiting for resource %s\n", name);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (समय_is_beक्रमe_eq_jअगरfies(warn_at)) अणु
			warn_at = jअगरfies + NFP_MUTEX_WAIT_NEXT_WARN * HZ;
			nfp_info(cpp, "waiting for NFP resource %s\n", name);
		पूर्ण
		अगर (msleep_पूर्णांकerruptible(10)) अणु
			nfp_err(cpp, "wait for resource %s interrupted\n",
				name);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * nfp_resource_cpp_id() - Return the cpp_id of a resource handle
 * @res:	NFP Resource handle
 *
 * Return: NFP CPP ID
 */
u32 nfp_resource_cpp_id(काष्ठा nfp_resource *res)
अणु
	वापस res->cpp_id;
पूर्ण

/**
 * nfp_resource_name() - Return the name of a resource handle
 * @res:	NFP Resource handle
 *
 * Return: स्थिर अक्षर poपूर्णांकer to the name of the resource
 */
स्थिर अक्षर *nfp_resource_name(काष्ठा nfp_resource *res)
अणु
	वापस res->name;
पूर्ण

/**
 * nfp_resource_address() - Return the address of a resource handle
 * @res:	NFP Resource handle
 *
 * Return: Address of the resource
 */
u64 nfp_resource_address(काष्ठा nfp_resource *res)
अणु
	वापस res->addr;
पूर्ण

/**
 * nfp_resource_size() - Return the size in bytes of a resource handle
 * @res:	NFP Resource handle
 *
 * Return: Size of the resource in bytes
 */
u64 nfp_resource_size(काष्ठा nfp_resource *res)
अणु
	वापस res->size;
पूर्ण

/**
 * nfp_resource_table_init() - Run initial checks on the resource table
 * @cpp:	NFP CPP handle
 *
 * Start-of-day init procedure क्रम resource table.  Must be called beक्रमe
 * any local resource table users may exist.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक nfp_resource_table_init(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_cpp_mutex *dev_mutex;
	पूर्णांक i, err;

	err = nfp_cpp_mutex_reclaim(cpp, NFP_RESOURCE_TBL_TARGET,
				    NFP_RESOURCE_TBL_BASE);
	अगर (err < 0) अणु
		nfp_err(cpp, "Error: failed to reclaim resource table mutex\n");
		वापस err;
	पूर्ण
	अगर (err)
		nfp_warn(cpp, "Warning: busted main resource table mutex\n");

	dev_mutex = nfp_cpp_mutex_alloc(cpp, NFP_RESOURCE_TBL_TARGET,
					NFP_RESOURCE_TBL_BASE,
					NFP_RESOURCE_TBL_KEY);
	अगर (!dev_mutex)
		वापस -ENOMEM;

	अगर (nfp_cpp_mutex_lock(dev_mutex)) अणु
		nfp_err(cpp, "Error: failed to claim resource table mutex\n");
		nfp_cpp_mutex_मुक्त(dev_mutex);
		वापस -EINVAL;
	पूर्ण

	/* Resource 0 is the dev_mutex, start from 1 */
	क्रम (i = 1; i < NFP_RESOURCE_TBL_ENTRIES; i++) अणु
		u64 addr = NFP_RESOURCE_TBL_BASE +
			माप(काष्ठा nfp_resource_entry) * i;

		err = nfp_cpp_mutex_reclaim(cpp, NFP_RESOURCE_TBL_TARGET, addr);
		अगर (err < 0) अणु
			nfp_err(cpp,
				"Error: failed to reclaim resource %d mutex\n",
				i);
			जाओ err_unlock;
		पूर्ण
		अगर (err)
			nfp_warn(cpp, "Warning: busted resource %d mutex\n", i);
	पूर्ण

	err = 0;
err_unlock:
	nfp_cpp_mutex_unlock(dev_mutex);
	nfp_cpp_mutex_मुक्त(dev_mutex);

	वापस err;
पूर्ण
