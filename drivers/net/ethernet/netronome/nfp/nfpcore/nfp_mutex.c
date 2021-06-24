<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश "nfp_cpp.h"
#समावेश "nfp6000/nfp6000.h"

काष्ठा nfp_cpp_mutex अणु
	काष्ठा nfp_cpp *cpp;
	पूर्णांक target;
	u16 depth;
	अचिन्हित दीर्घ दीर्घ address;
	u32 key;
पूर्ण;

अटल u32 nfp_mutex_locked(u16 पूर्णांकerface)
अणु
	वापस (u32)पूर्णांकerface << 16 | 0x000f;
पूर्ण

अटल u32 nfp_mutex_unlocked(u16 पूर्णांकerface)
अणु
	वापस (u32)पूर्णांकerface << 16 | 0x0000;
पूर्ण

अटल u32 nfp_mutex_owner(u32 val)
अणु
	वापस val >> 16;
पूर्ण

अटल bool nfp_mutex_is_locked(u32 val)
अणु
	वापस (val & 0xffff) == 0x000f;
पूर्ण

अटल bool nfp_mutex_is_unlocked(u32 val)
अणु
	वापस (val & 0xffff) == 0000;
पूर्ण

/* If you need more than 65536 recursive locks, please rethink your code. */
#घोषणा NFP_MUTEX_DEPTH_MAX         0xffff

अटल पूर्णांक
nfp_cpp_mutex_validate(u16 पूर्णांकerface, पूर्णांक *target, अचिन्हित दीर्घ दीर्घ address)
अणु
	/* Not permitted on invalid पूर्णांकerfaces */
	अगर (NFP_CPP_INTERFACE_TYPE_of(पूर्णांकerface) ==
	    NFP_CPP_INTERFACE_TYPE_INVALID)
		वापस -EINVAL;

	/* Address must be 64-bit aligned */
	अगर (address & 7)
		वापस -EINVAL;

	अगर (*target != NFP_CPP_TARGET_MU)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_mutex_init() - Initialize a mutex location
 * @cpp:	NFP CPP handle
 * @target:	NFP CPP target ID (ie NFP_CPP_TARGET_CLS or NFP_CPP_TARGET_MU)
 * @address:	Offset पूर्णांकo the address space of the NFP CPP target ID
 * @key:	Unique 32-bit value क्रम this mutex
 *
 * The CPP target:address must poपूर्णांक to a 64-bit aligned location, and
 * will initialize 64 bits of data at the location.
 *
 * This creates the initial mutex state, as locked by this
 * nfp_cpp_पूर्णांकerface().
 *
 * This function should only be called when setting up
 * the initial lock state upon boot-up of the प्रणाली.
 *
 * Return: 0 on success, or -त्रुटि_सं on failure
 */
पूर्णांक nfp_cpp_mutex_init(काष्ठा nfp_cpp *cpp,
		       पूर्णांक target, अचिन्हित दीर्घ दीर्घ address, u32 key)
अणु
	स्थिर u32 muw = NFP_CPP_ID(target, 4, 0);    /* atomic_ग_लिखो */
	u16 पूर्णांकerface = nfp_cpp_पूर्णांकerface(cpp);
	पूर्णांक err;

	err = nfp_cpp_mutex_validate(पूर्णांकerface, &target, address);
	अगर (err)
		वापस err;

	err = nfp_cpp_ग_लिखोl(cpp, muw, address + 4, key);
	अगर (err)
		वापस err;

	err = nfp_cpp_ग_लिखोl(cpp, muw, address, nfp_mutex_locked(पूर्णांकerface));
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_mutex_alloc() - Create a mutex handle
 * @cpp:	NFP CPP handle
 * @target:	NFP CPP target ID (ie NFP_CPP_TARGET_CLS or NFP_CPP_TARGET_MU)
 * @address:	Offset पूर्णांकo the address space of the NFP CPP target ID
 * @key:	32-bit unique key (must match the key at this location)
 *
 * The CPP target:address must poपूर्णांक to a 64-bit aligned location, and
 * reserve 64 bits of data at the location क्रम use by the handle.
 *
 * Only target/address pairs that poपूर्णांक to entities that support the
 * MU Atomic Engine's CmpAndSwap32 command are supported.
 *
 * Return:	A non-शून्य काष्ठा nfp_cpp_mutex * on success, शून्य on failure.
 */
काष्ठा nfp_cpp_mutex *nfp_cpp_mutex_alloc(काष्ठा nfp_cpp *cpp, पूर्णांक target,
					  अचिन्हित दीर्घ दीर्घ address, u32 key)
अणु
	स्थिर u32 mur = NFP_CPP_ID(target, 3, 0);    /* atomic_पढ़ो */
	u16 पूर्णांकerface = nfp_cpp_पूर्णांकerface(cpp);
	काष्ठा nfp_cpp_mutex *mutex;
	पूर्णांक err;
	u32 पंचांगp;

	err = nfp_cpp_mutex_validate(पूर्णांकerface, &target, address);
	अगर (err)
		वापस शून्य;

	err = nfp_cpp_पढ़ोl(cpp, mur, address + 4, &पंचांगp);
	अगर (err < 0)
		वापस शून्य;

	अगर (पंचांगp != key)
		वापस शून्य;

	mutex = kzalloc(माप(*mutex), GFP_KERNEL);
	अगर (!mutex)
		वापस शून्य;

	mutex->cpp = cpp;
	mutex->target = target;
	mutex->address = address;
	mutex->key = key;
	mutex->depth = 0;

	वापस mutex;
पूर्ण

/**
 * nfp_cpp_mutex_मुक्त() - Free a mutex handle - करोes not alter the lock state
 * @mutex:	NFP CPP Mutex handle
 */
व्योम nfp_cpp_mutex_मुक्त(काष्ठा nfp_cpp_mutex *mutex)
अणु
	kमुक्त(mutex);
पूर्ण

/**
 * nfp_cpp_mutex_lock() - Lock a mutex handle, using the NFP MU Atomic Engine
 * @mutex:	NFP CPP Mutex handle
 *
 * Return: 0 on success, or -त्रुटि_सं on failure
 */
पूर्णांक nfp_cpp_mutex_lock(काष्ठा nfp_cpp_mutex *mutex)
अणु
	अचिन्हित दीर्घ warn_at = jअगरfies + NFP_MUTEX_WAIT_FIRST_WARN * HZ;
	अचिन्हित दीर्घ err_at = jअगरfies + NFP_MUTEX_WAIT_ERROR * HZ;
	अचिन्हित पूर्णांक समयout_ms = 1;
	पूर्णांक err;

	/* We can't use a रुकोqueue here, because the unlocker
	 * might be on a separate CPU.
	 *
	 * So just रुको क्रम now.
	 */
	क्रम (;;) अणु
		err = nfp_cpp_mutex_trylock(mutex);
		अगर (err != -EBUSY)
			अवरोध;

		err = msleep_पूर्णांकerruptible(समयout_ms);
		अगर (err != 0) अणु
			nfp_info(mutex->cpp,
				 "interrupted waiting for NFP mutex\n");
			वापस -ERESTARTSYS;
		पूर्ण

		अगर (समय_is_beक्रमe_eq_jअगरfies(warn_at)) अणु
			warn_at = jअगरfies + NFP_MUTEX_WAIT_NEXT_WARN * HZ;
			nfp_warn(mutex->cpp,
				 "Warning: waiting for NFP mutex [depth:%hd target:%d addr:%llx key:%08x]\n",
				 mutex->depth,
				 mutex->target, mutex->address, mutex->key);
		पूर्ण
		अगर (समय_is_beक्रमe_eq_jअगरfies(err_at)) अणु
			nfp_err(mutex->cpp, "Error: mutex wait timed out\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * nfp_cpp_mutex_unlock() - Unlock a mutex handle, using the MU Atomic Engine
 * @mutex:	NFP CPP Mutex handle
 *
 * Return: 0 on success, or -त्रुटि_सं on failure
 */
पूर्णांक nfp_cpp_mutex_unlock(काष्ठा nfp_cpp_mutex *mutex)
अणु
	स्थिर u32 muw = NFP_CPP_ID(mutex->target, 4, 0);    /* atomic_ग_लिखो */
	स्थिर u32 mur = NFP_CPP_ID(mutex->target, 3, 0);    /* atomic_पढ़ो */
	काष्ठा nfp_cpp *cpp = mutex->cpp;
	u32 key, value;
	u16 पूर्णांकerface;
	पूर्णांक err;

	पूर्णांकerface = nfp_cpp_पूर्णांकerface(cpp);

	अगर (mutex->depth > 1) अणु
		mutex->depth--;
		वापस 0;
	पूर्ण

	err = nfp_cpp_पढ़ोl(mutex->cpp, mur, mutex->address + 4, &key);
	अगर (err < 0)
		वापस err;

	अगर (key != mutex->key)
		वापस -EPERM;

	err = nfp_cpp_पढ़ोl(mutex->cpp, mur, mutex->address, &value);
	अगर (err < 0)
		वापस err;

	अगर (value != nfp_mutex_locked(पूर्णांकerface))
		वापस -EACCES;

	err = nfp_cpp_ग_लिखोl(cpp, muw, mutex->address,
			     nfp_mutex_unlocked(पूर्णांकerface));
	अगर (err < 0)
		वापस err;

	mutex->depth = 0;
	वापस 0;
पूर्ण

/**
 * nfp_cpp_mutex_trylock() - Attempt to lock a mutex handle
 * @mutex:	NFP CPP Mutex handle
 *
 * Return:      0 अगर the lock succeeded, -त्रुटि_सं on failure
 */
पूर्णांक nfp_cpp_mutex_trylock(काष्ठा nfp_cpp_mutex *mutex)
अणु
	स्थिर u32 muw = NFP_CPP_ID(mutex->target, 4, 0);    /* atomic_ग_लिखो */
	स्थिर u32 mus = NFP_CPP_ID(mutex->target, 5, 3);    /* test_set_imm */
	स्थिर u32 mur = NFP_CPP_ID(mutex->target, 3, 0);    /* atomic_पढ़ो */
	काष्ठा nfp_cpp *cpp = mutex->cpp;
	u32 key, value, पंचांगp;
	पूर्णांक err;

	अगर (mutex->depth > 0) अणु
		अगर (mutex->depth == NFP_MUTEX_DEPTH_MAX)
			वापस -E2BIG;
		mutex->depth++;
		वापस 0;
	पूर्ण

	/* Verअगरy that the lock marker is not damaged */
	err = nfp_cpp_पढ़ोl(cpp, mur, mutex->address + 4, &key);
	अगर (err < 0)
		वापस err;

	अगर (key != mutex->key)
		वापस -EPERM;

	/* Compare against the unlocked state, and अगर true,
	 * ग_लिखो the पूर्णांकerface id पूर्णांकo the top 16 bits, and
	 * mark as locked.
	 */
	value = nfp_mutex_locked(nfp_cpp_पूर्णांकerface(cpp));

	/* We use test_set_imm here, as it implies a पढ़ो
	 * of the current state, and sets the bits in the
	 * bytemask of the command to 1s. Since the mutex
	 * is guaranteed to be 64-bit aligned, the bytemask
	 * of this 32-bit command is ensured to be 8'b00001111,
	 * which implies that the lower 4 bits will be set to
	 * ones regardless of the initial state.
	 *
	 * Since this is a 'Readback' operation, with no Pull
	 * data, we can treat this as a normal Push (पढ़ो)
	 * atomic, which वापसs the original value.
	 */
	err = nfp_cpp_पढ़ोl(cpp, mus, mutex->address, &पंचांगp);
	अगर (err < 0)
		वापस err;

	/* Was it unlocked? */
	अगर (nfp_mutex_is_unlocked(पंचांगp)) अणु
		/* The पढ़ो value can only be 0x....0000 in the unlocked state.
		 * If there was another contending क्रम this lock, then
		 * the lock state would be 0x....000f
		 */

		/* Write our owner ID पूर्णांकo the lock
		 * While not strictly necessary, this helps with
		 * debug and bookkeeping.
		 */
		err = nfp_cpp_ग_लिखोl(cpp, muw, mutex->address, value);
		अगर (err < 0)
			वापस err;

		mutex->depth = 1;
		वापस 0;
	पूर्ण

	वापस nfp_mutex_is_locked(पंचांगp) ? -EBUSY : -EINVAL;
पूर्ण

/**
 * nfp_cpp_mutex_reclaim() - Unlock mutex अगर held by local endpoपूर्णांक
 * @cpp:	NFP CPP handle
 * @target:	NFP CPP target ID (ie NFP_CPP_TARGET_CLS or NFP_CPP_TARGET_MU)
 * @address:	Offset पूर्णांकo the address space of the NFP CPP target ID
 *
 * Release lock अगर held by local प्रणाली.  Extreme care is advised, call only
 * when no local lock users can exist.
 *
 * Return:      0 अगर the lock was OK, 1 अगर locked by us, -त्रुटि_सं on invalid mutex
 */
पूर्णांक nfp_cpp_mutex_reclaim(काष्ठा nfp_cpp *cpp, पूर्णांक target,
			  अचिन्हित दीर्घ दीर्घ address)
अणु
	स्थिर u32 mur = NFP_CPP_ID(target, 3, 0);	/* atomic_पढ़ो */
	स्थिर u32 muw = NFP_CPP_ID(target, 4, 0);	/* atomic_ग_लिखो */
	u16 पूर्णांकerface = nfp_cpp_पूर्णांकerface(cpp);
	पूर्णांक err;
	u32 पंचांगp;

	err = nfp_cpp_mutex_validate(पूर्णांकerface, &target, address);
	अगर (err)
		वापस err;

	/* Check lock */
	err = nfp_cpp_पढ़ोl(cpp, mur, address, &पंचांगp);
	अगर (err < 0)
		वापस err;

	अगर (nfp_mutex_is_unlocked(पंचांगp) || nfp_mutex_owner(पंचांगp) != पूर्णांकerface)
		वापस 0;

	/* Bust the lock */
	err = nfp_cpp_ग_लिखोl(cpp, muw, address, nfp_mutex_unlocked(पूर्णांकerface));
	अगर (err < 0)
		वापस err;

	वापस 1;
पूर्ण
