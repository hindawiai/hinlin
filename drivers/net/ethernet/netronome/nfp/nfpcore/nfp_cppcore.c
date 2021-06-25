<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_cppcore.c
 * Provides low-level access to the NFP's पूर्णांकernal CPP bus
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश "nfp_arm.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp6000/nfp6000.h"

#घोषणा NFP_ARM_GCSR_SOFTMODEL2                              0x0000014c
#घोषणा NFP_ARM_GCSR_SOFTMODEL3                              0x00000150

काष्ठा nfp_cpp_resource अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	u32 cpp_id;
	u64 start;
	u64 end;
पूर्ण;

/**
 * काष्ठा nfp_cpp - मुख्य nfpcore device काष्ठाure
 * Following fields are पढ़ो-only after probe() निकासs or netdevs are spawned.
 * @dev:		embedded device काष्ठाure
 * @op:			low-level implementation ops
 * @priv:		निजी data of the low-level implementation
 * @model:		chip model
 * @पूर्णांकerface:		chip पूर्णांकerface id we are using to reach it
 * @serial:		chip serial number
 * @imb_cat_table:	CPP Mapping Table
 * @mu_locality_lsb:	MU access type bit offset
 *
 * Following fields use explicit locking:
 * @resource_list:	NFP CPP resource list
 * @resource_lock:	protects @resource_list
 *
 * @area_cache_list:	cached areas क्रम cpp/xpb पढ़ो/ग_लिखो speed up
 * @area_cache_mutex:	protects @area_cache_list
 *
 * @रुकोq:		area रुको queue
 */
काष्ठा nfp_cpp अणु
	काष्ठा device dev;

	व्योम *priv;

	u32 model;
	u16 पूर्णांकerface;
	u8 serial[NFP_SERIAL_LEN];

	स्थिर काष्ठा nfp_cpp_operations *op;
	काष्ठा list_head resource_list;
	rwlock_t resource_lock;
	रुको_queue_head_t रुकोq;

	u32 imb_cat_table[16];
	अचिन्हित पूर्णांक mu_locality_lsb;

	काष्ठा mutex area_cache_mutex;
	काष्ठा list_head area_cache_list;
पूर्ण;

/* Element of the area_cache_list */
काष्ठा nfp_cpp_area_cache अणु
	काष्ठा list_head entry;
	u32 id;
	u64 addr;
	u32 size;
	काष्ठा nfp_cpp_area *area;
पूर्ण;

काष्ठा nfp_cpp_area अणु
	काष्ठा nfp_cpp *cpp;
	काष्ठा kref kref;
	atomic_t refcount;
	काष्ठा mutex mutex;	/* Lock क्रम the area's refcount */
	अचिन्हित दीर्घ दीर्घ offset;
	अचिन्हित दीर्घ size;
	काष्ठा nfp_cpp_resource resource;
	व्योम __iomem *iomem;
	/* Here follows the 'priv' part of nfp_cpp_area. */
पूर्ण;

काष्ठा nfp_cpp_explicit अणु
	काष्ठा nfp_cpp *cpp;
	काष्ठा nfp_cpp_explicit_command cmd;
	/* Here follows the 'priv' part of nfp_cpp_area. */
पूर्ण;

अटल व्योम __resource_add(काष्ठा list_head *head, काष्ठा nfp_cpp_resource *res)
अणु
	काष्ठा nfp_cpp_resource *पंचांगp;
	काष्ठा list_head *pos;

	list_क्रम_each(pos, head) अणु
		पंचांगp = container_of(pos, काष्ठा nfp_cpp_resource, list);

		अगर (पंचांगp->cpp_id > res->cpp_id)
			अवरोध;

		अगर (पंचांगp->cpp_id == res->cpp_id && पंचांगp->start > res->start)
			अवरोध;
	पूर्ण

	list_add_tail(&res->list, pos);
पूर्ण

अटल व्योम __resource_del(काष्ठा nfp_cpp_resource *res)
अणु
	list_del_init(&res->list);
पूर्ण

अटल व्योम __release_cpp_area(काष्ठा kref *kref)
अणु
	काष्ठा nfp_cpp_area *area =
		container_of(kref, काष्ठा nfp_cpp_area, kref);
	काष्ठा nfp_cpp *cpp = nfp_cpp_area_cpp(area);

	अगर (area->cpp->op->area_cleanup)
		area->cpp->op->area_cleanup(area);

	ग_लिखो_lock(&cpp->resource_lock);
	__resource_del(&area->resource);
	ग_लिखो_unlock(&cpp->resource_lock);
	kमुक्त(area);
पूर्ण

अटल व्योम nfp_cpp_area_put(काष्ठा nfp_cpp_area *area)
अणु
	kref_put(&area->kref, __release_cpp_area);
पूर्ण

अटल काष्ठा nfp_cpp_area *nfp_cpp_area_get(काष्ठा nfp_cpp_area *area)
अणु
	kref_get(&area->kref);

	वापस area;
पूर्ण

/**
 * nfp_cpp_मुक्त() - मुक्त the CPP handle
 * @cpp:	CPP handle
 */
व्योम nfp_cpp_मुक्त(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_cpp_area_cache *cache, *cपंचांगp;
	काष्ठा nfp_cpp_resource *res, *rपंचांगp;

	/* Remove all caches */
	list_क्रम_each_entry_safe(cache, cपंचांगp, &cpp->area_cache_list, entry) अणु
		list_del(&cache->entry);
		अगर (cache->id)
			nfp_cpp_area_release(cache->area);
		nfp_cpp_area_मुक्त(cache->area);
		kमुक्त(cache);
	पूर्ण

	/* There should be no dangling areas at this poपूर्णांक */
	WARN_ON(!list_empty(&cpp->resource_list));

	/* .. but अगर they weren't, try to clean up. */
	list_क्रम_each_entry_safe(res, rपंचांगp, &cpp->resource_list, list) अणु
		काष्ठा nfp_cpp_area *area = container_of(res,
							 काष्ठा nfp_cpp_area,
							 resource);

		dev_err(cpp->dev.parent, "Dangling area: %d:%d:%d:0x%0llx-0x%0llx%s%s\n",
			NFP_CPP_ID_TARGET_of(res->cpp_id),
			NFP_CPP_ID_ACTION_of(res->cpp_id),
			NFP_CPP_ID_TOKEN_of(res->cpp_id),
			res->start, res->end,
			res->name ? " " : "",
			res->name ? res->name : "");

		अगर (area->cpp->op->area_release)
			area->cpp->op->area_release(area);

		__release_cpp_area(&area->kref);
	पूर्ण

	अगर (cpp->op->मुक्त)
		cpp->op->मुक्त(cpp);

	device_unरेजिस्टर(&cpp->dev);

	kमुक्त(cpp);
पूर्ण

/**
 * nfp_cpp_model() - Retrieve the Model ID of the NFP
 * @cpp:	NFP CPP handle
 *
 * Return: NFP CPP Model ID
 */
u32 nfp_cpp_model(काष्ठा nfp_cpp *cpp)
अणु
	वापस cpp->model;
पूर्ण

/**
 * nfp_cpp_पूर्णांकerface() - Retrieve the Interface ID of the NFP
 * @cpp:	NFP CPP handle
 *
 * Return: NFP CPP Interface ID
 */
u16 nfp_cpp_पूर्णांकerface(काष्ठा nfp_cpp *cpp)
अणु
	वापस cpp->पूर्णांकerface;
पूर्ण

/**
 * nfp_cpp_serial() - Retrieve the Serial ID of the NFP
 * @cpp:	NFP CPP handle
 * @serial:	Poपूर्णांकer to NFP serial number
 *
 * Return:  Length of NFP serial number
 */
पूर्णांक nfp_cpp_serial(काष्ठा nfp_cpp *cpp, स्थिर u8 **serial)
अणु
	*serial = &cpp->serial[0];
	वापस माप(cpp->serial);
पूर्ण

#घोषणा NFP_IMB_TGTADDRESSMODECFG_MODE_of(_x)		(((_x) >> 13) & 0x7)
#घोषणा NFP_IMB_TGTADDRESSMODECFG_ADDRMODE		BIT(12)
#घोषणा   NFP_IMB_TGTADDRESSMODECFG_ADDRMODE_32_BIT	0
#घोषणा   NFP_IMB_TGTADDRESSMODECFG_ADDRMODE_40_BIT	BIT(12)

अटल पूर्णांक nfp_cpp_set_mu_locality_lsb(काष्ठा nfp_cpp *cpp)
अणु
	अचिन्हित पूर्णांक mode, addr40;
	u32 imbcppat;
	पूर्णांक res;

	imbcppat = cpp->imb_cat_table[NFP_CPP_TARGET_MU];
	mode = NFP_IMB_TGTADDRESSMODECFG_MODE_of(imbcppat);
	addr40 = !!(imbcppat & NFP_IMB_TGTADDRESSMODECFG_ADDRMODE);

	res = nfp_cppat_mu_locality_lsb(mode, addr40);
	अगर (res < 0)
		वापस res;
	cpp->mu_locality_lsb = res;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक nfp_cpp_mu_locality_lsb(काष्ठा nfp_cpp *cpp)
अणु
	वापस cpp->mu_locality_lsb;
पूर्ण

/**
 * nfp_cpp_area_alloc_with_name() - allocate a new CPP area
 * @cpp:	CPP device handle
 * @dest:	NFP CPP ID
 * @name:	Name of region
 * @address:	Address of region
 * @size:	Size of region
 *
 * Allocate and initialize a CPP area काष्ठाure.  The area must later
 * be locked करोwn with an 'acquire' beक्रमe it can be safely accessed.
 *
 * NOTE: @address and @size must be 32-bit aligned values.
 *
 * Return: NFP CPP area handle, or शून्य
 */
काष्ठा nfp_cpp_area *
nfp_cpp_area_alloc_with_name(काष्ठा nfp_cpp *cpp, u32 dest, स्थिर अक्षर *name,
			     अचिन्हित दीर्घ दीर्घ address, अचिन्हित दीर्घ size)
अणु
	काष्ठा nfp_cpp_area *area;
	u64 पंचांगp64 = address;
	पूर्णांक err, name_len;

	/* Remap from cpp_island to cpp_target */
	err = nfp_target_cpp(dest, पंचांगp64, &dest, &पंचांगp64, cpp->imb_cat_table);
	अगर (err < 0)
		वापस शून्य;

	address = पंचांगp64;

	अगर (!name)
		name = "(reserved)";

	name_len = म_माप(name) + 1;
	area = kzalloc(माप(*area) + cpp->op->area_priv_size + name_len,
		       GFP_KERNEL);
	अगर (!area)
		वापस शून्य;

	area->cpp = cpp;
	area->resource.name = (व्योम *)area + माप(*area) +
		cpp->op->area_priv_size;
	स_नकल((अक्षर *)area->resource.name, name, name_len);

	area->resource.cpp_id = dest;
	area->resource.start = address;
	area->resource.end = area->resource.start + size - 1;
	INIT_LIST_HEAD(&area->resource.list);

	atomic_set(&area->refcount, 0);
	kref_init(&area->kref);
	mutex_init(&area->mutex);

	अगर (cpp->op->area_init) अणु
		पूर्णांक err;

		err = cpp->op->area_init(area, dest, address, size);
		अगर (err < 0) अणु
			kमुक्त(area);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ग_लिखो_lock(&cpp->resource_lock);
	__resource_add(&cpp->resource_list, &area->resource);
	ग_लिखो_unlock(&cpp->resource_lock);

	area->offset = address;
	area->size = size;

	वापस area;
पूर्ण

/**
 * nfp_cpp_area_alloc() - allocate a new CPP area
 * @cpp:	CPP handle
 * @dest:	CPP id
 * @address:	Start address on CPP target
 * @size:	Size of area in bytes
 *
 * Allocate and initialize a CPP area काष्ठाure.  The area must later
 * be locked करोwn with an 'acquire' beक्रमe it can be safely accessed.
 *
 * NOTE: @address and @size must be 32-bit aligned values.
 *
 * Return: NFP CPP Area handle, or शून्य
 */
काष्ठा nfp_cpp_area *
nfp_cpp_area_alloc(काष्ठा nfp_cpp *cpp, u32 dest,
		   अचिन्हित दीर्घ दीर्घ address, अचिन्हित दीर्घ size)
अणु
	वापस nfp_cpp_area_alloc_with_name(cpp, dest, शून्य, address, size);
पूर्ण

/**
 * nfp_cpp_area_alloc_acquire() - allocate a new CPP area and lock it करोwn
 * @cpp:	CPP handle
 * @name:	Name of region
 * @dest:	CPP id
 * @address:	Start address on CPP target
 * @size:	Size of area
 *
 * Allocate and initialize a CPP area काष्ठाure, and lock it करोwn so
 * that it can be accessed directly.
 *
 * NOTE: @address and @size must be 32-bit aligned values.
 * The area must also be 'released' when the काष्ठाure is मुक्तd.
 *
 * Return: NFP CPP Area handle, or शून्य
 */
काष्ठा nfp_cpp_area *
nfp_cpp_area_alloc_acquire(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, u32 dest,
			   अचिन्हित दीर्घ दीर्घ address, अचिन्हित दीर्घ size)
अणु
	काष्ठा nfp_cpp_area *area;

	area = nfp_cpp_area_alloc_with_name(cpp, dest, name, address, size);
	अगर (!area)
		वापस शून्य;

	अगर (nfp_cpp_area_acquire(area)) अणु
		nfp_cpp_area_मुक्त(area);
		वापस शून्य;
	पूर्ण

	वापस area;
पूर्ण

/**
 * nfp_cpp_area_मुक्त() - मुक्त up the CPP area
 * @area:	CPP area handle
 *
 * Frees up memory resources held by the CPP area.
 */
व्योम nfp_cpp_area_मुक्त(काष्ठा nfp_cpp_area *area)
अणु
	अगर (atomic_पढ़ो(&area->refcount))
		nfp_warn(area->cpp, "Warning: freeing busy area\n");
	nfp_cpp_area_put(area);
पूर्ण

अटल bool nfp_cpp_area_acquire_try(काष्ठा nfp_cpp_area *area, पूर्णांक *status)
अणु
	*status = area->cpp->op->area_acquire(area);

	वापस *status != -EAGAIN;
पूर्ण

अटल पूर्णांक __nfp_cpp_area_acquire(काष्ठा nfp_cpp_area *area)
अणु
	पूर्णांक err, status;

	अगर (atomic_inc_वापस(&area->refcount) > 1)
		वापस 0;

	अगर (!area->cpp->op->area_acquire)
		वापस 0;

	err = रुको_event_पूर्णांकerruptible(area->cpp->रुकोq,
				       nfp_cpp_area_acquire_try(area, &status));
	अगर (!err)
		err = status;
	अगर (err) अणु
		nfp_warn(area->cpp, "Warning: area wait failed: %d\n", err);
		atomic_dec(&area->refcount);
		वापस err;
	पूर्ण

	nfp_cpp_area_get(area);

	वापस 0;
पूर्ण

/**
 * nfp_cpp_area_acquire() - lock करोwn a CPP area क्रम access
 * @area:	CPP area handle
 *
 * Locks करोwn the CPP area क्रम a potential दीर्घ term activity.  Area
 * must always be locked करोwn beक्रमe being accessed.
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_area_acquire(काष्ठा nfp_cpp_area *area)
अणु
	पूर्णांक ret;

	mutex_lock(&area->mutex);
	ret = __nfp_cpp_area_acquire(area);
	mutex_unlock(&area->mutex);

	वापस ret;
पूर्ण

/**
 * nfp_cpp_area_acquire_nonblocking() - lock करोwn a CPP area क्रम access
 * @area:	CPP area handle
 *
 * Locks करोwn the CPP area क्रम a potential दीर्घ term activity.  Area
 * must always be locked करोwn beक्रमe being accessed.
 *
 * NOTE: Returns -EAGAIN is no area is available
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_area_acquire_nonblocking(काष्ठा nfp_cpp_area *area)
अणु
	mutex_lock(&area->mutex);
	अगर (atomic_inc_वापस(&area->refcount) == 1) अणु
		अगर (area->cpp->op->area_acquire) अणु
			पूर्णांक err;

			err = area->cpp->op->area_acquire(area);
			अगर (err < 0) अणु
				atomic_dec(&area->refcount);
				mutex_unlock(&area->mutex);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&area->mutex);

	nfp_cpp_area_get(area);
	वापस 0;
पूर्ण

/**
 * nfp_cpp_area_release() - release a locked करोwn CPP area
 * @area:	CPP area handle
 *
 * Releases a previously locked करोwn CPP area.
 */
व्योम nfp_cpp_area_release(काष्ठा nfp_cpp_area *area)
अणु
	mutex_lock(&area->mutex);
	/* Only call the release on refcount == 0 */
	अगर (atomic_dec_and_test(&area->refcount)) अणु
		अगर (area->cpp->op->area_release) अणु
			area->cpp->op->area_release(area);
			/* Let anyone रुकोing क्रम a BAR try to get one.. */
			wake_up_पूर्णांकerruptible_all(&area->cpp->रुकोq);
		पूर्ण
	पूर्ण
	mutex_unlock(&area->mutex);

	nfp_cpp_area_put(area);
पूर्ण

/**
 * nfp_cpp_area_release_मुक्त() - release CPP area and मुक्त it
 * @area:	CPP area handle
 *
 * Releases CPP area and मुक्तs up memory resources held by the it.
 */
व्योम nfp_cpp_area_release_मुक्त(काष्ठा nfp_cpp_area *area)
अणु
	nfp_cpp_area_release(area);
	nfp_cpp_area_मुक्त(area);
पूर्ण

/**
 * nfp_cpp_area_पढ़ो() - पढ़ो data from CPP area
 * @area:	  CPP area handle
 * @offset:	  offset पूर्णांकo CPP area
 * @kernel_vaddr: kernel address to put data पूर्णांकo
 * @length:	  number of bytes to पढ़ो
 *
 * Read data from indicated CPP region.
 *
 * NOTE: @offset and @length must be 32-bit aligned values.
 * Area must have been locked करोwn with an 'acquire'.
 *
 * Return: length of io, or -ERRNO
 */
पूर्णांक nfp_cpp_area_पढ़ो(काष्ठा nfp_cpp_area *area,
		      अचिन्हित दीर्घ offset, व्योम *kernel_vaddr,
		      माप_प्रकार length)
अणु
	वापस area->cpp->op->area_पढ़ो(area, kernel_vaddr, offset, length);
पूर्ण

/**
 * nfp_cpp_area_ग_लिखो() - ग_लिखो data to CPP area
 * @area:	CPP area handle
 * @offset:	offset पूर्णांकo CPP area
 * @kernel_vaddr: kernel address to पढ़ो data from
 * @length:	number of bytes to ग_लिखो
 *
 * Write data to indicated CPP region.
 *
 * NOTE: @offset and @length must be 32-bit aligned values.
 * Area must have been locked करोwn with an 'acquire'.
 *
 * Return: length of io, or -ERRNO
 */
पूर्णांक nfp_cpp_area_ग_लिखो(काष्ठा nfp_cpp_area *area,
		       अचिन्हित दीर्घ offset, स्थिर व्योम *kernel_vaddr,
		       माप_प्रकार length)
अणु
	वापस area->cpp->op->area_ग_लिखो(area, kernel_vaddr, offset, length);
पूर्ण

/**
 * nfp_cpp_area_size() - वापस size of a CPP area
 * @cpp_area:	CPP area handle
 *
 * Return: Size of the area
 */
माप_प्रकार nfp_cpp_area_size(काष्ठा nfp_cpp_area *cpp_area)
अणु
	वापस cpp_area->size;
पूर्ण

/**
 * nfp_cpp_area_name() - वापस name of a CPP area
 * @cpp_area:	CPP area handle
 *
 * Return: Name of the area, or शून्य
 */
स्थिर अक्षर *nfp_cpp_area_name(काष्ठा nfp_cpp_area *cpp_area)
अणु
	वापस cpp_area->resource.name;
पूर्ण

/**
 * nfp_cpp_area_priv() - वापस निजी काष्ठा क्रम CPP area
 * @cpp_area:	CPP area handle
 *
 * Return: Private data क्रम the CPP area
 */
व्योम *nfp_cpp_area_priv(काष्ठा nfp_cpp_area *cpp_area)
अणु
	वापस &cpp_area[1];
पूर्ण

/**
 * nfp_cpp_area_cpp() - वापस CPP handle क्रम CPP area
 * @cpp_area:	CPP area handle
 *
 * Return: NFP CPP handle
 */
काष्ठा nfp_cpp *nfp_cpp_area_cpp(काष्ठा nfp_cpp_area *cpp_area)
अणु
	वापस cpp_area->cpp;
पूर्ण

/**
 * nfp_cpp_area_resource() - get resource
 * @area:	CPP area handle
 *
 * NOTE: Area must have been locked करोwn with an 'acquire'.
 *
 * Return: काष्ठा resource poपूर्णांकer, or शून्य
 */
काष्ठा resource *nfp_cpp_area_resource(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा resource *res = शून्य;

	अगर (area->cpp->op->area_resource)
		res = area->cpp->op->area_resource(area);

	वापस res;
पूर्ण

/**
 * nfp_cpp_area_phys() - get physical address of CPP area
 * @area:	CPP area handle
 *
 * NOTE: Area must have been locked करोwn with an 'acquire'.
 *
 * Return: phy_addr_t of the area, or शून्य
 */
phys_addr_t nfp_cpp_area_phys(काष्ठा nfp_cpp_area *area)
अणु
	phys_addr_t addr = ~0;

	अगर (area->cpp->op->area_phys)
		addr = area->cpp->op->area_phys(area);

	वापस addr;
पूर्ण

/**
 * nfp_cpp_area_iomem() - get IOMEM region क्रम CPP area
 * @area:	CPP area handle
 *
 * Returns an iomem poपूर्णांकer क्रम use with पढ़ोl()/ग_लिखोl() style
 * operations.
 *
 * NOTE: Area must have been locked करोwn with an 'acquire'.
 *
 * Return: __iomem poपूर्णांकer to the area, or शून्य
 */
व्योम __iomem *nfp_cpp_area_iomem(काष्ठा nfp_cpp_area *area)
अणु
	व्योम __iomem *iomem = शून्य;

	अगर (area->cpp->op->area_iomem)
		iomem = area->cpp->op->area_iomem(area);

	वापस iomem;
पूर्ण

/**
 * nfp_cpp_area_पढ़ोl() - Read a u32 word from an area
 * @area:	CPP Area handle
 * @offset:	Offset पूर्णांकo area
 * @value:	Poपूर्णांकer to पढ़ो buffer
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_area_पढ़ोl(काष्ठा nfp_cpp_area *area,
		       अचिन्हित दीर्घ offset, u32 *value)
अणु
	u8 पंचांगp[4];
	पूर्णांक n;

	n = nfp_cpp_area_पढ़ो(area, offset, &पंचांगp, माप(पंचांगp));
	अगर (n != माप(पंचांगp))
		वापस n < 0 ? n : -EIO;

	*value = get_unaligned_le32(पंचांगp);
	वापस 0;
पूर्ण

/**
 * nfp_cpp_area_ग_लिखोl() - Write a u32 word to an area
 * @area:	CPP Area handle
 * @offset:	Offset पूर्णांकo area
 * @value:	Value to ग_लिखो
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_area_ग_लिखोl(काष्ठा nfp_cpp_area *area,
			अचिन्हित दीर्घ offset, u32 value)
अणु
	u8 पंचांगp[4];
	पूर्णांक n;

	put_unaligned_le32(value, पंचांगp);
	n = nfp_cpp_area_ग_लिखो(area, offset, &पंचांगp, माप(पंचांगp));

	वापस n == माप(पंचांगp) ? 0 : n < 0 ? n : -EIO;
पूर्ण

/**
 * nfp_cpp_area_पढ़ोq() - Read a u64 word from an area
 * @area:	CPP Area handle
 * @offset:	Offset पूर्णांकo area
 * @value:	Poपूर्णांकer to पढ़ो buffer
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_area_पढ़ोq(काष्ठा nfp_cpp_area *area,
		       अचिन्हित दीर्घ offset, u64 *value)
अणु
	u8 पंचांगp[8];
	पूर्णांक n;

	n = nfp_cpp_area_पढ़ो(area, offset, &पंचांगp, माप(पंचांगp));
	अगर (n != माप(पंचांगp))
		वापस n < 0 ? n : -EIO;

	*value = get_unaligned_le64(पंचांगp);
	वापस 0;
पूर्ण

/**
 * nfp_cpp_area_ग_लिखोq() - Write a u64 word to an area
 * @area:	CPP Area handle
 * @offset:	Offset पूर्णांकo area
 * @value:	Value to ग_लिखो
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_area_ग_लिखोq(काष्ठा nfp_cpp_area *area,
			अचिन्हित दीर्घ offset, u64 value)
अणु
	u8 पंचांगp[8];
	पूर्णांक n;

	put_unaligned_le64(value, पंचांगp);
	n = nfp_cpp_area_ग_लिखो(area, offset, &पंचांगp, माप(पंचांगp));

	वापस n == माप(पंचांगp) ? 0 : n < 0 ? n : -EIO;
पूर्ण

/**
 * nfp_cpp_area_fill() - fill a CPP area with a value
 * @area:	CPP area
 * @offset:	offset पूर्णांकo CPP area
 * @value:	value to fill with
 * @length:	length of area to fill
 *
 * Fill indicated area with given value.
 *
 * Return: length of io, or -ERRNO
 */
पूर्णांक nfp_cpp_area_fill(काष्ठा nfp_cpp_area *area,
		      अचिन्हित दीर्घ offset, u32 value, माप_प्रकार length)
अणु
	u8 पंचांगp[4];
	माप_प्रकार i;
	पूर्णांक k;

	put_unaligned_le32(value, पंचांगp);

	अगर (offset % माप(पंचांगp) || length % माप(पंचांगp))
		वापस -EINVAL;

	क्रम (i = 0; i < length; i += माप(पंचांगp)) अणु
		k = nfp_cpp_area_ग_लिखो(area, offset + i, &पंचांगp, माप(पंचांगp));
		अगर (k < 0)
			वापस k;
	पूर्ण

	वापस i;
पूर्ण

/**
 * nfp_cpp_area_cache_add() - Permanently reserve and area क्रम the hot cache
 * @cpp:	NFP CPP handle
 * @size:	Size of the area - MUST BE A POWER OF 2.
 */
पूर्णांक nfp_cpp_area_cache_add(काष्ठा nfp_cpp *cpp, माप_प्रकार size)
अणु
	काष्ठा nfp_cpp_area_cache *cache;
	काष्ठा nfp_cpp_area *area;

	/* Allocate an area - we use the MU target's base as a placeholder,
	 * as all supported chips have a MU.
	 */
	area = nfp_cpp_area_alloc(cpp, NFP_CPP_ID(7, NFP_CPP_ACTION_RW, 0),
				  0, size);
	अगर (!area)
		वापस -ENOMEM;

	cache = kzalloc(माप(*cache), GFP_KERNEL);
	अगर (!cache)
		वापस -ENOMEM;

	cache->id = 0;
	cache->addr = 0;
	cache->size = size;
	cache->area = area;
	mutex_lock(&cpp->area_cache_mutex);
	list_add_tail(&cache->entry, &cpp->area_cache_list);
	mutex_unlock(&cpp->area_cache_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा nfp_cpp_area_cache *
area_cache_get(काष्ठा nfp_cpp *cpp, u32 id,
	       u64 addr, अचिन्हित दीर्घ *offset, माप_प्रकार length)
अणु
	काष्ठा nfp_cpp_area_cache *cache;
	पूर्णांक err;

	/* Early निकास when length == 0, which prevents
	 * the need क्रम special हाल code below when
	 * checking against available cache size.
	 */
	अगर (length == 0 || id == 0)
		वापस शून्य;

	/* Remap from cpp_island to cpp_target */
	err = nfp_target_cpp(id, addr, &id, &addr, cpp->imb_cat_table);
	अगर (err < 0)
		वापस शून्य;

	mutex_lock(&cpp->area_cache_mutex);

	अगर (list_empty(&cpp->area_cache_list)) अणु
		mutex_unlock(&cpp->area_cache_mutex);
		वापस शून्य;
	पूर्ण

	addr += *offset;

	/* See अगर we have a match */
	list_क्रम_each_entry(cache, &cpp->area_cache_list, entry) अणु
		अगर (id == cache->id &&
		    addr >= cache->addr &&
		    addr + length <= cache->addr + cache->size)
			जाओ निकास;
	पूर्ण

	/* No matches - inspect the tail of the LRU */
	cache = list_entry(cpp->area_cache_list.prev,
			   काष्ठा nfp_cpp_area_cache, entry);

	/* Can we fit in the cache entry? */
	अगर (round_करोwn(addr + length - 1, cache->size) !=
	    round_करोwn(addr, cache->size)) अणु
		mutex_unlock(&cpp->area_cache_mutex);
		वापस शून्य;
	पूर्ण

	/* If id != 0, we will need to release it */
	अगर (cache->id) अणु
		nfp_cpp_area_release(cache->area);
		cache->id = 0;
		cache->addr = 0;
	पूर्ण

	/* Adjust the start address to be cache size aligned */
	cache->id = id;
	cache->addr = addr & ~(u64)(cache->size - 1);

	/* Re-init to the new ID and address */
	अगर (cpp->op->area_init) अणु
		err = cpp->op->area_init(cache->area,
					 id, cache->addr, cache->size);
		अगर (err < 0) अणु
			mutex_unlock(&cpp->area_cache_mutex);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* Attempt to acquire */
	err = nfp_cpp_area_acquire(cache->area);
	अगर (err < 0) अणु
		mutex_unlock(&cpp->area_cache_mutex);
		वापस शून्य;
	पूर्ण

निकास:
	/* Adjust offset */
	*offset = addr - cache->addr;
	वापस cache;
पूर्ण

अटल व्योम
area_cache_put(काष्ठा nfp_cpp *cpp, काष्ठा nfp_cpp_area_cache *cache)
अणु
	अगर (!cache)
		वापस;

	/* Move to front of LRU */
	list_del(&cache->entry);
	list_add(&cache->entry, &cpp->area_cache_list);

	mutex_unlock(&cpp->area_cache_mutex);
पूर्ण

अटल पूर्णांक __nfp_cpp_पढ़ो(काष्ठा nfp_cpp *cpp, u32 destination,
			  अचिन्हित दीर्घ दीर्घ address, व्योम *kernel_vaddr,
			  माप_प्रकार length)
अणु
	काष्ठा nfp_cpp_area_cache *cache;
	काष्ठा nfp_cpp_area *area;
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक err;

	cache = area_cache_get(cpp, destination, address, &offset, length);
	अगर (cache) अणु
		area = cache->area;
	पूर्ण अन्यथा अणु
		area = nfp_cpp_area_alloc(cpp, destination, address, length);
		अगर (!area)
			वापस -ENOMEM;

		err = nfp_cpp_area_acquire(area);
		अगर (err) अणु
			nfp_cpp_area_मुक्त(area);
			वापस err;
		पूर्ण
	पूर्ण

	err = nfp_cpp_area_पढ़ो(area, offset, kernel_vaddr, length);

	अगर (cache)
		area_cache_put(cpp, cache);
	अन्यथा
		nfp_cpp_area_release_मुक्त(area);

	वापस err;
पूर्ण

/**
 * nfp_cpp_पढ़ो() - पढ़ो from CPP target
 * @cpp:		CPP handle
 * @destination:	CPP id
 * @address:		offset पूर्णांकo CPP target
 * @kernel_vaddr:	kernel buffer क्रम result
 * @length:		number of bytes to पढ़ो
 *
 * Return: length of io, or -ERRNO
 */
पूर्णांक nfp_cpp_पढ़ो(काष्ठा nfp_cpp *cpp, u32 destination,
		 अचिन्हित दीर्घ दीर्घ address, व्योम *kernel_vaddr,
		 माप_प्रकार length)
अणु
	माप_प्रकार n, offset;
	पूर्णांक ret;

	क्रम (offset = 0; offset < length; offset += n) अणु
		अचिन्हित दीर्घ दीर्घ r_addr = address + offset;

		/* make first पढ़ो smaller to align to safe winकरोw */
		n = min_t(माप_प्रकार, length - offset,
			  ALIGN(r_addr + 1, NFP_CPP_SAFE_AREA_SIZE) - r_addr);

		ret = __nfp_cpp_पढ़ो(cpp, destination, address + offset,
				     kernel_vaddr + offset, n);
		अगर (ret < 0)
			वापस ret;
		अगर (ret != n)
			वापस offset + n;
	पूर्ण

	वापस length;
पूर्ण

अटल पूर्णांक __nfp_cpp_ग_लिखो(काष्ठा nfp_cpp *cpp, u32 destination,
			   अचिन्हित दीर्घ दीर्घ address,
			   स्थिर व्योम *kernel_vaddr, माप_प्रकार length)
अणु
	काष्ठा nfp_cpp_area_cache *cache;
	काष्ठा nfp_cpp_area *area;
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक err;

	cache = area_cache_get(cpp, destination, address, &offset, length);
	अगर (cache) अणु
		area = cache->area;
	पूर्ण अन्यथा अणु
		area = nfp_cpp_area_alloc(cpp, destination, address, length);
		अगर (!area)
			वापस -ENOMEM;

		err = nfp_cpp_area_acquire(area);
		अगर (err) अणु
			nfp_cpp_area_मुक्त(area);
			वापस err;
		पूर्ण
	पूर्ण

	err = nfp_cpp_area_ग_लिखो(area, offset, kernel_vaddr, length);

	अगर (cache)
		area_cache_put(cpp, cache);
	अन्यथा
		nfp_cpp_area_release_मुक्त(area);

	वापस err;
पूर्ण

/**
 * nfp_cpp_ग_लिखो() - ग_लिखो to CPP target
 * @cpp:		CPP handle
 * @destination:	CPP id
 * @address:		offset पूर्णांकo CPP target
 * @kernel_vaddr:	kernel buffer to पढ़ो from
 * @length:		number of bytes to ग_लिखो
 *
 * Return: length of io, or -ERRNO
 */
पूर्णांक nfp_cpp_ग_लिखो(काष्ठा nfp_cpp *cpp, u32 destination,
		  अचिन्हित दीर्घ दीर्घ address,
		  स्थिर व्योम *kernel_vaddr, माप_प्रकार length)
अणु
	माप_प्रकार n, offset;
	पूर्णांक ret;

	क्रम (offset = 0; offset < length; offset += n) अणु
		अचिन्हित दीर्घ दीर्घ w_addr = address + offset;

		/* make first ग_लिखो smaller to align to safe winकरोw */
		n = min_t(माप_प्रकार, length - offset,
			  ALIGN(w_addr + 1, NFP_CPP_SAFE_AREA_SIZE) - w_addr);

		ret = __nfp_cpp_ग_लिखो(cpp, destination, address + offset,
				      kernel_vaddr + offset, n);
		अगर (ret < 0)
			वापस ret;
		अगर (ret != n)
			वापस offset + n;
	पूर्ण

	वापस length;
पूर्ण

/* Return the correct CPP address, and fixup xpb_addr as needed. */
अटल u32 nfp_xpb_to_cpp(काष्ठा nfp_cpp *cpp, u32 *xpb_addr)
अणु
	पूर्णांक island;
	u32 xpb;

	xpb = NFP_CPP_ID(14, NFP_CPP_ACTION_RW, 0);
	/* Ensure that non-local XPB accesses go
	 * out through the global XPBM bus.
	 */
	island = (*xpb_addr >> 24) & 0x3f;
	अगर (!island)
		वापस xpb;

	अगर (island != 1) अणु
		*xpb_addr |= 1 << 30;
		वापस xpb;
	पूर्ण

	/* Accesses to the ARM Island overlay uses Island 0 / Global Bit */
	*xpb_addr &= ~0x7f000000;
	अगर (*xpb_addr < 0x60000) अणु
		*xpb_addr |= 1 << 30;
	पूर्ण अन्यथा अणु
		/* And only non-ARM पूर्णांकerfaces use the island id = 1 */
		अगर (NFP_CPP_INTERFACE_TYPE_of(nfp_cpp_पूर्णांकerface(cpp))
		    != NFP_CPP_INTERFACE_TYPE_ARM)
			*xpb_addr |= 1 << 24;
	पूर्ण

	वापस xpb;
पूर्ण

/**
 * nfp_xpb_पढ़ोl() - Read a u32 word from a XPB location
 * @cpp:	CPP device handle
 * @xpb_addr:	Address क्रम operation
 * @value:	Poपूर्णांकer to पढ़ो buffer
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_xpb_पढ़ोl(काष्ठा nfp_cpp *cpp, u32 xpb_addr, u32 *value)
अणु
	u32 cpp_dest = nfp_xpb_to_cpp(cpp, &xpb_addr);

	वापस nfp_cpp_पढ़ोl(cpp, cpp_dest, xpb_addr, value);
पूर्ण

/**
 * nfp_xpb_ग_लिखोl() - Write a u32 word to a XPB location
 * @cpp:	CPP device handle
 * @xpb_addr:	Address क्रम operation
 * @value:	Value to ग_लिखो
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_xpb_ग_लिखोl(काष्ठा nfp_cpp *cpp, u32 xpb_addr, u32 value)
अणु
	u32 cpp_dest = nfp_xpb_to_cpp(cpp, &xpb_addr);

	वापस nfp_cpp_ग_लिखोl(cpp, cpp_dest, xpb_addr, value);
पूर्ण

/**
 * nfp_xpb_ग_लिखोlm() - Modअगरy bits of a 32-bit value from the XPB bus
 * @cpp:	NFP CPP device handle
 * @xpb_tgt:	XPB target and address
 * @mask:	mask of bits to alter
 * @value:	value to modअगरy
 *
 * KERNEL: This operation is safe to call in पूर्णांकerrupt or softirq context.
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_xpb_ग_लिखोlm(काष्ठा nfp_cpp *cpp, u32 xpb_tgt,
		    u32 mask, u32 value)
अणु
	पूर्णांक err;
	u32 पंचांगp;

	err = nfp_xpb_पढ़ोl(cpp, xpb_tgt, &पंचांगp);
	अगर (err < 0)
		वापस err;

	पंचांगp &= ~mask;
	पंचांगp |= mask & value;
	वापस nfp_xpb_ग_लिखोl(cpp, xpb_tgt, पंचांगp);
पूर्ण

/* Lockdep markers */
अटल काष्ठा lock_class_key nfp_cpp_resource_lock_key;

अटल व्योम nfp_cpp_dev_release(काष्ठा device *dev)
अणु
	/* Nothing to करो here - it just makes the kernel happy */
पूर्ण

/**
 * nfp_cpp_from_operations() - Create a NFP CPP handle
 *                             from an operations काष्ठाure
 * @ops:	NFP CPP operations काष्ठाure
 * @parent:	Parent device
 * @priv:	Private data of low-level implementation
 *
 * NOTE: On failure, cpp_ops->मुक्त will be called!
 *
 * Return: NFP CPP handle on success, ERR_PTR on failure
 */
काष्ठा nfp_cpp *
nfp_cpp_from_operations(स्थिर काष्ठा nfp_cpp_operations *ops,
			काष्ठा device *parent, व्योम *priv)
अणु
	स्थिर u32 arm = NFP_CPP_ID(NFP_CPP_TARGET_ARM, NFP_CPP_ACTION_RW, 0);
	काष्ठा nfp_cpp *cpp;
	पूर्णांक अगरc, err;
	u32 mask[2];
	u32 xpbaddr;
	माप_प्रकार tgt;

	cpp = kzalloc(माप(*cpp), GFP_KERNEL);
	अगर (!cpp) अणु
		err = -ENOMEM;
		जाओ err_दो_स्मृति;
	पूर्ण

	cpp->op = ops;
	cpp->priv = priv;

	अगरc = ops->get_पूर्णांकerface(parent);
	अगर (अगरc < 0) अणु
		err = अगरc;
		जाओ err_मुक्त_cpp;
	पूर्ण
	cpp->पूर्णांकerface = अगरc;
	अगर (ops->पढ़ो_serial) अणु
		err = ops->पढ़ो_serial(parent, cpp->serial);
		अगर (err)
			जाओ err_मुक्त_cpp;
	पूर्ण

	rwlock_init(&cpp->resource_lock);
	init_रुकोqueue_head(&cpp->रुकोq);
	lockdep_set_class(&cpp->resource_lock, &nfp_cpp_resource_lock_key);
	INIT_LIST_HEAD(&cpp->resource_list);
	INIT_LIST_HEAD(&cpp->area_cache_list);
	mutex_init(&cpp->area_cache_mutex);
	cpp->dev.init_name = "cpp";
	cpp->dev.parent = parent;
	cpp->dev.release = nfp_cpp_dev_release;
	err = device_रेजिस्टर(&cpp->dev);
	अगर (err < 0) अणु
		put_device(&cpp->dev);
		जाओ err_मुक्त_cpp;
	पूर्ण

	dev_set_drvdata(&cpp->dev, cpp);

	/* NOTE: cpp_lock is NOT locked क्रम op->init,
	 * since it may call NFP CPP API operations
	 */
	अगर (cpp->op->init) अणु
		err = cpp->op->init(cpp);
		अगर (err < 0) अणु
			dev_err(parent,
				"NFP interface initialization failed\n");
			जाओ err_out;
		पूर्ण
	पूर्ण

	err = nfp_cpp_model_स्वतःdetect(cpp, &cpp->model);
	अगर (err < 0) अणु
		dev_err(parent, "NFP model detection failed\n");
		जाओ err_out;
	पूर्ण

	क्रम (tgt = 0; tgt < ARRAY_SIZE(cpp->imb_cat_table); tgt++) अणु
			/* Hardcoded XPB IMB Base, island 0 */
		xpbaddr = 0x000a0000 + (tgt * 4);
		err = nfp_xpb_पढ़ोl(cpp, xpbaddr,
				    &cpp->imb_cat_table[tgt]);
		अगर (err < 0) अणु
			dev_err(parent,
				"Can't read CPP mapping from device\n");
			जाओ err_out;
		पूर्ण
	पूर्ण

	nfp_cpp_पढ़ोl(cpp, arm, NFP_ARM_GCSR + NFP_ARM_GCSR_SOFTMODEL2,
		      &mask[0]);
	nfp_cpp_पढ़ोl(cpp, arm, NFP_ARM_GCSR + NFP_ARM_GCSR_SOFTMODEL3,
		      &mask[1]);

	err = nfp_cpp_set_mu_locality_lsb(cpp);
	अगर (err < 0) अणु
		dev_err(parent,	"Can't calculate MU locality bit offset\n");
		जाओ err_out;
	पूर्ण

	dev_info(cpp->dev.parent, "Model: 0x%08x, SN: %pM, Ifc: 0x%04x\n",
		 nfp_cpp_model(cpp), cpp->serial, nfp_cpp_पूर्णांकerface(cpp));

	वापस cpp;

err_out:
	device_unरेजिस्टर(&cpp->dev);
err_मुक्त_cpp:
	kमुक्त(cpp);
err_दो_स्मृति:
	वापस ERR_PTR(err);
पूर्ण

/**
 * nfp_cpp_priv() - Get the operations निजी data of a CPP handle
 * @cpp:	CPP handle
 *
 * Return: Private data क्रम the NFP CPP handle
 */
व्योम *nfp_cpp_priv(काष्ठा nfp_cpp *cpp)
अणु
	वापस cpp->priv;
पूर्ण

/**
 * nfp_cpp_device() - Get the Linux device handle of a CPP handle
 * @cpp:	CPP handle
 *
 * Return: Device क्रम the NFP CPP bus
 */
काष्ठा device *nfp_cpp_device(काष्ठा nfp_cpp *cpp)
अणु
	वापस &cpp->dev;
पूर्ण

#घोषणा NFP_EXPL_OP(func, expl, args...)			  \
	(अणु							  \
		काष्ठा nfp_cpp *cpp = nfp_cpp_explicit_cpp(expl); \
		पूर्णांक err = -ENODEV;				  \
								  \
		अगर (cpp->op->func)				  \
			err = cpp->op->func(expl, ##args);	  \
		err;						  \
	पूर्ण)

#घोषणा NFP_EXPL_OP_NR(func, expl, args...)			  \
	(अणु							  \
		काष्ठा nfp_cpp *cpp = nfp_cpp_explicit_cpp(expl); \
								  \
		अगर (cpp->op->func)				  \
			cpp->op->func(expl, ##args);		  \
								  \
	पूर्ण)

/**
 * nfp_cpp_explicit_acquire() - Acquire explicit access handle
 * @cpp:	NFP CPP handle
 *
 * The 'data_ref' and 'signal_ref' values are useful when
 * स्थिरructing the NFP_EXPL_CSR1 and NFP_EXPL_POST values.
 *
 * Return: NFP CPP explicit handle
 */
काष्ठा nfp_cpp_explicit *nfp_cpp_explicit_acquire(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_cpp_explicit *expl;
	पूर्णांक err;

	expl = kzalloc(माप(*expl) + cpp->op->explicit_priv_size, GFP_KERNEL);
	अगर (!expl)
		वापस शून्य;

	expl->cpp = cpp;
	err = NFP_EXPL_OP(explicit_acquire, expl);
	अगर (err < 0) अणु
		kमुक्त(expl);
		वापस शून्य;
	पूर्ण

	वापस expl;
पूर्ण

/**
 * nfp_cpp_explicit_set_target() - Set target fields क्रम explicit
 * @expl:	Explicit handle
 * @cpp_id:	CPP ID field
 * @len:	CPP Length field
 * @mask:	CPP Mask field
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_set_target(काष्ठा nfp_cpp_explicit *expl,
				u32 cpp_id, u8 len, u8 mask)
अणु
	expl->cmd.cpp_id = cpp_id;
	expl->cmd.len = len;
	expl->cmd.byte_mask = mask;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_explicit_set_data() - Set data fields क्रम explicit
 * @expl:	Explicit handle
 * @data_master: CPP Data Master field
 * @data_ref:	CPP Data Ref field
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_set_data(काष्ठा nfp_cpp_explicit *expl,
			      u8 data_master, u16 data_ref)
अणु
	expl->cmd.data_master = data_master;
	expl->cmd.data_ref = data_ref;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_explicit_set_संकेत() - Set संकेत fields क्रम explicit
 * @expl:	Explicit handle
 * @संकेत_master: CPP Signal Master field
 * @संकेत_ref:	CPP Signal Ref field
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_set_संकेत(काष्ठा nfp_cpp_explicit *expl,
				u8 संकेत_master, u8 संकेत_ref)
अणु
	expl->cmd.संकेत_master = संकेत_master;
	expl->cmd.संकेत_ref = संकेत_ref;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_explicit_set_posted() - Set completion fields क्रम explicit
 * @expl:	Explicit handle
 * @posted:	True क्रम संकेतed completion, false otherwise
 * @siga:	CPP Signal A field
 * @siga_mode:	CPP Signal A Mode field
 * @sigb:	CPP Signal B field
 * @sigb_mode:	CPP Signal B Mode field
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_set_posted(काष्ठा nfp_cpp_explicit *expl, पूर्णांक posted,
				u8 siga,
				क्रमागत nfp_cpp_explicit_संकेत_mode siga_mode,
				u8 sigb,
				क्रमागत nfp_cpp_explicit_संकेत_mode sigb_mode)
अणु
	expl->cmd.posted = posted;
	expl->cmd.siga = siga;
	expl->cmd.sigb = sigb;
	expl->cmd.siga_mode = siga_mode;
	expl->cmd.sigb_mode = sigb_mode;

	वापस 0;
पूर्ण

/**
 * nfp_cpp_explicit_put() - Set up the ग_लिखो (pull) data क्रम a explicit access
 * @expl:	NFP CPP Explicit handle
 * @buff:	Data to have the target pull in the transaction
 * @len:	Length of data, in bytes
 *
 * The 'len' parameter must be less than or equal to 128 bytes.
 *
 * If this function is called beक्रमe the configuration
 * रेजिस्टरs are set, it will वापस -EINVAL.
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_put(काष्ठा nfp_cpp_explicit *expl,
			 स्थिर व्योम *buff, माप_प्रकार len)
अणु
	वापस NFP_EXPL_OP(explicit_put, expl, buff, len);
पूर्ण

/**
 * nfp_cpp_explicit_करो() - Execute a transaction, and रुको क्रम it to complete
 * @expl:	NFP CPP Explicit handle
 * @address:	Address to send in the explicit transaction
 *
 * If this function is called beक्रमe the configuration
 * रेजिस्टरs are set, it will वापस -1, with an त्रुटि_सं of EINVAL.
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_करो(काष्ठा nfp_cpp_explicit *expl, u64 address)
अणु
	वापस NFP_EXPL_OP(explicit_करो, expl, &expl->cmd, address);
पूर्ण

/**
 * nfp_cpp_explicit_get() - Get the 'push' (पढ़ो) data from a explicit access
 * @expl:	NFP CPP Explicit handle
 * @buff:	Data that the target pushed in the transaction
 * @len:	Length of data, in bytes
 *
 * The 'len' parameter must be less than or equal to 128 bytes.
 *
 * If this function is called beक्रमe all three configuration
 * रेजिस्टरs are set, it will वापस -1, with an त्रुटि_सं of EINVAL.
 *
 * If this function is called beक्रमe nfp_cpp_explicit_करो()
 * has completed, it will वापस -1, with an त्रुटि_सं of EBUSY.
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_cpp_explicit_get(काष्ठा nfp_cpp_explicit *expl, व्योम *buff, माप_प्रकार len)
अणु
	वापस NFP_EXPL_OP(explicit_get, expl, buff, len);
पूर्ण

/**
 * nfp_cpp_explicit_release() - Release explicit access handle
 * @expl:	NFP CPP Explicit handle
 *
 */
व्योम nfp_cpp_explicit_release(काष्ठा nfp_cpp_explicit *expl)
अणु
	NFP_EXPL_OP_NR(explicit_release, expl);
	kमुक्त(expl);
पूर्ण

/**
 * nfp_cpp_explicit_cpp() - वापस CPP handle क्रम CPP explicit
 * @cpp_explicit:	CPP explicit handle
 *
 * Return: NFP CPP handle of the explicit
 */
काष्ठा nfp_cpp *nfp_cpp_explicit_cpp(काष्ठा nfp_cpp_explicit *cpp_explicit)
अणु
	वापस cpp_explicit->cpp;
पूर्ण

/**
 * nfp_cpp_explicit_priv() - वापस निजी काष्ठा क्रम CPP explicit
 * @cpp_explicit:	CPP explicit handle
 *
 * Return: निजी data of the explicit, or शून्य
 */
व्योम *nfp_cpp_explicit_priv(काष्ठा nfp_cpp_explicit *cpp_explicit)
अणु
	वापस &cpp_explicit[1];
पूर्ण
