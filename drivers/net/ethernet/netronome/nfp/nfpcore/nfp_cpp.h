<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_cpp.h
 * Interface क्रम low-level NFP CPP access.
 * Authors: Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */
#अगर_अघोषित __NFP_CPP_H__
#घोषणा __NFP_CPP_H__

#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>

#अगर_अघोषित NFP_SUBSYS
#घोषणा NFP_SUBSYS "nfp"
#पूर्ण_अगर

#घोषणा nfp_err(cpp, fmt, args...) \
	dev_err(nfp_cpp_device(cpp)->parent, NFP_SUBSYS ": " fmt, ## args)
#घोषणा nfp_warn(cpp, fmt, args...) \
	dev_warn(nfp_cpp_device(cpp)->parent, NFP_SUBSYS ": " fmt, ## args)
#घोषणा nfp_info(cpp, fmt, args...) \
	dev_info(nfp_cpp_device(cpp)->parent, NFP_SUBSYS ": " fmt, ## args)
#घोषणा nfp_dbg(cpp, fmt, args...) \
	dev_dbg(nfp_cpp_device(cpp)->parent, NFP_SUBSYS ": " fmt, ## args)
#घोषणा nfp_prपूर्णांकk(level, cpp, fmt, args...) \
	dev_prपूर्णांकk(level, nfp_cpp_device(cpp)->parent,	\
		   NFP_SUBSYS ": " fmt,	## args)

#घोषणा PCI_64BIT_BAR_COUNT             3

/* NFP hardware venकरोr/device ids.
 */
#घोषणा PCI_DEVICE_ID_NETRONOME_NFP3800	0x3800

#घोषणा NFP_CPP_NUM_TARGETS             16
/* Max size of area it should be safe to request */
#घोषणा NFP_CPP_SAFE_AREA_SIZE		SZ_2M

/* NFP_MUTEX_WAIT_* are समयouts in seconds when रुकोing क्रम a mutex */
#घोषणा NFP_MUTEX_WAIT_FIRST_WARN	15
#घोषणा NFP_MUTEX_WAIT_NEXT_WARN	5
#घोषणा NFP_MUTEX_WAIT_ERROR		60

काष्ठा device;

काष्ठा nfp_cpp_area;
काष्ठा nfp_cpp;
काष्ठा resource;

/* Wildcard indicating a CPP पढ़ो or ग_लिखो action
 *
 * The action used will be either पढ़ो or ग_लिखो depending on whether a
 * पढ़ो or ग_लिखो inकाष्ठाion/call is perक्रमmed on the NFP_CPP_ID.  It
 * is recomended that the RW action is used even अगर all actions to be
 * perक्रमmed on a NFP_CPP_ID are known to be only पढ़ोs or ग_लिखोs.
 * Doing so will in many हालs save NFP CPP पूर्णांकernal software
 * resources.
 */
#घोषणा NFP_CPP_ACTION_RW               32

#घोषणा NFP_CPP_TARGET_ID_MASK          0x1f

#घोषणा NFP_CPP_ATOMIC_RD(target, island) \
	NFP_CPP_ISLAND_ID((target), 3, 0, (island))
#घोषणा NFP_CPP_ATOMIC_WR(target, island) \
	NFP_CPP_ISLAND_ID((target), 4, 0, (island))

/**
 * NFP_CPP_ID() - pack target, token, and action पूर्णांकo a CPP ID.
 * @target:     NFP CPP target id
 * @action:     NFP CPP action id
 * @token:      NFP CPP token id
 *
 * Create a 32-bit CPP identअगरier representing the access to be made.
 * These identअगरiers are used as parameters to other NFP CPP
 * functions.  Some CPP devices may allow wildcard identअगरiers to be
 * specअगरied.
 *
 * Return:      NFP CPP ID
 */
#घोषणा NFP_CPP_ID(target, action, token)			 \
	((((target) & 0x7f) << 24) | (((token)  & 0xff) << 16) | \
	 (((action) & 0xff) <<  8))

/**
 * NFP_CPP_ISLAND_ID() - pack target, token, action, and island पूर्णांकo a CPP ID.
 * @target:     NFP CPP target id
 * @action:     NFP CPP action id
 * @token:      NFP CPP token id
 * @island:     NFP CPP island id
 *
 * Create a 32-bit CPP identअगरier representing the access to be made.
 * These identअगरiers are used as parameters to other NFP CPP
 * functions.  Some CPP devices may allow wildcard identअगरiers to be
 * specअगरied.
 *
 * Return:      NFP CPP ID
 */
#घोषणा NFP_CPP_ISLAND_ID(target, action, token, island)	 \
	((((target) & 0x7f) << 24) | (((token)  & 0xff) << 16) | \
	 (((action) & 0xff) <<  8) | (((island) & 0xff) << 0))

/**
 * NFP_CPP_ID_TARGET_of() - Return the NFP CPP target of a NFP CPP ID
 * @id:         NFP CPP ID
 *
 * Return:      NFP CPP target
 */
अटल अंतरभूत u8 NFP_CPP_ID_TARGET_of(u32 id)
अणु
	वापस (id >> 24) & NFP_CPP_TARGET_ID_MASK;
पूर्ण

/**
 * NFP_CPP_ID_TOKEN_of() - Return the NFP CPP token of a NFP CPP ID
 * @id:         NFP CPP ID
 * Return:      NFP CPP token
 */
अटल अंतरभूत u8 NFP_CPP_ID_TOKEN_of(u32 id)
अणु
	वापस (id >> 16) & 0xff;
पूर्ण

/**
 * NFP_CPP_ID_ACTION_of() - Return the NFP CPP action of a NFP CPP ID
 * @id:         NFP CPP ID
 *
 * Return:      NFP CPP action
 */
अटल अंतरभूत u8 NFP_CPP_ID_ACTION_of(u32 id)
अणु
	वापस (id >> 8) & 0xff;
पूर्ण

/**
 * NFP_CPP_ID_ISLAND_of() - Return the NFP CPP island of a NFP CPP ID
 * @id: NFP CPP ID
 *
 * Return:      NFP CPP island
 */
अटल अंतरभूत u8 NFP_CPP_ID_ISLAND_of(u32 id)
अणु
	वापस (id >> 0) & 0xff;
पूर्ण

/* NFP Interface types - logical पूर्णांकerface क्रम this CPP connection
 * 4 bits are reserved क्रम पूर्णांकerface type.
 */
#घोषणा NFP_CPP_INTERFACE_TYPE_INVALID      0x0
#घोषणा NFP_CPP_INTERFACE_TYPE_PCI          0x1
#घोषणा NFP_CPP_INTERFACE_TYPE_ARM          0x2
#घोषणा NFP_CPP_INTERFACE_TYPE_RPC          0x3
#घोषणा NFP_CPP_INTERFACE_TYPE_ILA          0x4

/**
 * NFP_CPP_INTERFACE() - Conकाष्ठा a 16-bit NFP Interface ID
 * @type:       NFP Interface Type
 * @unit:       Unit identअगरier क्रम the पूर्णांकerface type
 * @channel:    Channel identअगरier क्रम the पूर्णांकerface unit
 *
 * Interface IDs consists of 4 bits of पूर्णांकerface type,
 * 4 bits of unit identअगरier, and 8 bits of channel identअगरier.
 *
 * The NFP Interface ID is used in the implementation of
 * NFP CPP API mutexes, which use the MU Atomic CompareAndWrite
 * operation - hence the limit to 16 bits to be able to
 * use the NFP Interface ID as a lock owner.
 *
 * Return:      Interface ID
 */
#घोषणा NFP_CPP_INTERFACE(type, unit, channel)	\
	((((type) & 0xf) << 12) |		\
	 (((unit) & 0xf) <<  8) |		\
	 (((channel) & 0xff) << 0))

/**
 * NFP_CPP_INTERFACE_TYPE_of() - Get the पूर्णांकerface type
 * @पूर्णांकerface:  NFP Interface ID
 * Return:      NFP Interface ID's type
 */
#घोषणा NFP_CPP_INTERFACE_TYPE_of(पूर्णांकerface)   (((पूर्णांकerface) >> 12) & 0xf)

/**
 * NFP_CPP_INTERFACE_UNIT_of() - Get the पूर्णांकerface unit
 * @पूर्णांकerface:  NFP Interface ID
 * Return:      NFP Interface ID's unit
 */
#घोषणा NFP_CPP_INTERFACE_UNIT_of(पूर्णांकerface)   (((पूर्णांकerface) >>  8) & 0xf)

/**
 * NFP_CPP_INTERFACE_CHANNEL_of() - Get the पूर्णांकerface channel
 * @पूर्णांकerface:  NFP Interface ID
 * Return:      NFP Interface ID's channel
 */
#घोषणा NFP_CPP_INTERFACE_CHANNEL_of(पूर्णांकerface)   (((पूर्णांकerface) >>  0) & 0xff)

/* Implemented in nfp_cppcore.c */
व्योम nfp_cpp_मुक्त(काष्ठा nfp_cpp *cpp);
u32 nfp_cpp_model(काष्ठा nfp_cpp *cpp);
u16 nfp_cpp_पूर्णांकerface(काष्ठा nfp_cpp *cpp);
पूर्णांक nfp_cpp_serial(काष्ठा nfp_cpp *cpp, स्थिर u8 **serial);
अचिन्हित पूर्णांक nfp_cpp_mu_locality_lsb(काष्ठा nfp_cpp *cpp);

काष्ठा nfp_cpp_area *nfp_cpp_area_alloc_with_name(काष्ठा nfp_cpp *cpp,
						  u32 cpp_id,
						  स्थिर अक्षर *name,
						  अचिन्हित दीर्घ दीर्घ address,
						  अचिन्हित दीर्घ size);
काष्ठा nfp_cpp_area *nfp_cpp_area_alloc(काष्ठा nfp_cpp *cpp, u32 cpp_id,
					अचिन्हित दीर्घ दीर्घ address,
					अचिन्हित दीर्घ size);
काष्ठा nfp_cpp_area *
nfp_cpp_area_alloc_acquire(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, u32 cpp_id,
			   अचिन्हित दीर्घ दीर्घ address, अचिन्हित दीर्घ size);
व्योम nfp_cpp_area_मुक्त(काष्ठा nfp_cpp_area *area);
पूर्णांक nfp_cpp_area_acquire(काष्ठा nfp_cpp_area *area);
पूर्णांक nfp_cpp_area_acquire_nonblocking(काष्ठा nfp_cpp_area *area);
व्योम nfp_cpp_area_release(काष्ठा nfp_cpp_area *area);
व्योम nfp_cpp_area_release_मुक्त(काष्ठा nfp_cpp_area *area);
पूर्णांक nfp_cpp_area_पढ़ो(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
		      व्योम *buffer, माप_प्रकार length);
पूर्णांक nfp_cpp_area_ग_लिखो(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
		       स्थिर व्योम *buffer, माप_प्रकार length);
माप_प्रकार nfp_cpp_area_size(काष्ठा nfp_cpp_area *area);
स्थिर अक्षर *nfp_cpp_area_name(काष्ठा nfp_cpp_area *cpp_area);
व्योम *nfp_cpp_area_priv(काष्ठा nfp_cpp_area *cpp_area);
काष्ठा nfp_cpp *nfp_cpp_area_cpp(काष्ठा nfp_cpp_area *cpp_area);
काष्ठा resource *nfp_cpp_area_resource(काष्ठा nfp_cpp_area *area);
phys_addr_t nfp_cpp_area_phys(काष्ठा nfp_cpp_area *area);
व्योम __iomem *nfp_cpp_area_iomem(काष्ठा nfp_cpp_area *area);

पूर्णांक nfp_cpp_area_पढ़ोl(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
		       u32 *value);
पूर्णांक nfp_cpp_area_ग_लिखोl(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
			u32 value);
पूर्णांक nfp_cpp_area_पढ़ोq(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
		       u64 *value);
पूर्णांक nfp_cpp_area_ग_लिखोq(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
			u64 value);
पूर्णांक nfp_cpp_area_fill(काष्ठा nfp_cpp_area *area, अचिन्हित दीर्घ offset,
		      u32 value, माप_प्रकार length);

पूर्णांक nfp_xpb_पढ़ोl(काष्ठा nfp_cpp *cpp, u32 xpb_tgt, u32 *value);
पूर्णांक nfp_xpb_ग_लिखोl(काष्ठा nfp_cpp *cpp, u32 xpb_tgt, u32 value);
पूर्णांक nfp_xpb_ग_लिखोlm(काष्ठा nfp_cpp *cpp, u32 xpb_tgt, u32 mask, u32 value);

/* Implemented in nfp_cpplib.c */
पूर्णांक nfp_cpp_पढ़ो(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		 अचिन्हित दीर्घ दीर्घ address, व्योम *kernel_vaddr, माप_प्रकार length);
पूर्णांक nfp_cpp_ग_लिखो(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		  अचिन्हित दीर्घ दीर्घ address, स्थिर व्योम *kernel_vaddr,
		  माप_प्रकार length);
पूर्णांक nfp_cpp_पढ़ोl(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		  अचिन्हित दीर्घ दीर्घ address, u32 *value);
पूर्णांक nfp_cpp_ग_लिखोl(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		   अचिन्हित दीर्घ दीर्घ address, u32 value);
पूर्णांक nfp_cpp_पढ़ोq(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		  अचिन्हित दीर्घ दीर्घ address, u64 *value);
पूर्णांक nfp_cpp_ग_लिखोq(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		   अचिन्हित दीर्घ दीर्घ address, u64 value);

u8 __iomem *
nfp_cpp_map_area(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, u32 cpp_id, u64 addr,
		 अचिन्हित दीर्घ size, काष्ठा nfp_cpp_area **area);

काष्ठा nfp_cpp_mutex;

पूर्णांक nfp_cpp_mutex_init(काष्ठा nfp_cpp *cpp, पूर्णांक target,
		       अचिन्हित दीर्घ दीर्घ address, u32 key_id);
काष्ठा nfp_cpp_mutex *nfp_cpp_mutex_alloc(काष्ठा nfp_cpp *cpp, पूर्णांक target,
					  अचिन्हित दीर्घ दीर्घ address,
					  u32 key_id);
व्योम nfp_cpp_mutex_मुक्त(काष्ठा nfp_cpp_mutex *mutex);
पूर्णांक nfp_cpp_mutex_lock(काष्ठा nfp_cpp_mutex *mutex);
पूर्णांक nfp_cpp_mutex_unlock(काष्ठा nfp_cpp_mutex *mutex);
पूर्णांक nfp_cpp_mutex_trylock(काष्ठा nfp_cpp_mutex *mutex);
पूर्णांक nfp_cpp_mutex_reclaim(काष्ठा nfp_cpp *cpp, पूर्णांक target,
			  अचिन्हित दीर्घ दीर्घ address);

/**
 * nfp_cppcore_pcie_unit() - Get PCI Unit of a CPP handle
 * @cpp:	CPP handle
 *
 * Return: PCI unit क्रम the NFP CPP handle
 */
अटल अंतरभूत u8 nfp_cppcore_pcie_unit(काष्ठा nfp_cpp *cpp)
अणु
	वापस NFP_CPP_INTERFACE_UNIT_of(nfp_cpp_पूर्णांकerface(cpp));
पूर्ण

काष्ठा nfp_cpp_explicit;

काष्ठा nfp_cpp_explicit_command अणु
	u32 cpp_id;
	u16 data_ref;
	u8  data_master;
	u8  len;
	u8  byte_mask;
	u8  संकेत_master;
	u8  संकेत_ref;
	u8  posted;
	u8  siga;
	u8  sigb;
	s8   siga_mode;
	s8   sigb_mode;
पूर्ण;

#घोषणा NFP_SERIAL_LEN		6

/**
 * काष्ठा nfp_cpp_operations - NFP CPP operations काष्ठाure
 * @area_priv_size:     Size of the nfp_cpp_area निजी data
 * @owner:              Owner module
 * @init:               Initialize the NFP CPP bus
 * @मुक्त:               Free the bus
 * @पढ़ो_serial:	Read serial number to memory provided
 * @get_पूर्णांकerface:	Return CPP पूर्णांकerface
 * @area_init:          Initialize a new NFP CPP area (not serialized)
 * @area_cleanup:       Clean up a NFP CPP area (not serialized)
 * @area_acquire:       Acquire the NFP CPP area (serialized)
 * @area_release:       Release area (serialized)
 * @area_resource:      Get resource range of area (not serialized)
 * @area_phys:          Get physical address of area (not serialized)
 * @area_iomem:         Get iomem of area (not serialized)
 * @area_पढ़ो:          Perक्रमm a पढ़ो from a NFP CPP area (serialized)
 * @area_ग_लिखो:         Perक्रमm a ग_लिखो to a NFP CPP area (serialized)
 * @explicit_priv_size: Size of an explicit's निजी area
 * @explicit_acquire:   Acquire an explicit area
 * @explicit_release:   Release an explicit area
 * @explicit_put:       Write data to send
 * @explicit_get:       Read data received
 * @explicit_करो:        Perक्रमm the transaction
 */
काष्ठा nfp_cpp_operations अणु
	माप_प्रकार area_priv_size;
	काष्ठा module *owner;

	पूर्णांक (*init)(काष्ठा nfp_cpp *cpp);
	व्योम (*मुक्त)(काष्ठा nfp_cpp *cpp);

	पूर्णांक (*पढ़ो_serial)(काष्ठा device *dev, u8 *serial);
	पूर्णांक (*get_पूर्णांकerface)(काष्ठा device *dev);

	पूर्णांक (*area_init)(काष्ठा nfp_cpp_area *area,
			 u32 dest, अचिन्हित दीर्घ दीर्घ address,
			 अचिन्हित दीर्घ size);
	व्योम (*area_cleanup)(काष्ठा nfp_cpp_area *area);
	पूर्णांक (*area_acquire)(काष्ठा nfp_cpp_area *area);
	व्योम (*area_release)(काष्ठा nfp_cpp_area *area);
	काष्ठा resource *(*area_resource)(काष्ठा nfp_cpp_area *area);
	phys_addr_t (*area_phys)(काष्ठा nfp_cpp_area *area);
	व्योम __iomem *(*area_iomem)(काष्ठा nfp_cpp_area *area);
	पूर्णांक (*area_पढ़ो)(काष्ठा nfp_cpp_area *area, व्योम *kernel_vaddr,
			 अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक length);
	पूर्णांक (*area_ग_लिखो)(काष्ठा nfp_cpp_area *area, स्थिर व्योम *kernel_vaddr,
			  अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक length);

	माप_प्रकार explicit_priv_size;
	पूर्णांक (*explicit_acquire)(काष्ठा nfp_cpp_explicit *expl);
	व्योम (*explicit_release)(काष्ठा nfp_cpp_explicit *expl);
	पूर्णांक (*explicit_put)(काष्ठा nfp_cpp_explicit *expl,
			    स्थिर व्योम *buff, माप_प्रकार len);
	पूर्णांक (*explicit_get)(काष्ठा nfp_cpp_explicit *expl,
			    व्योम *buff, माप_प्रकार len);
	पूर्णांक (*explicit_करो)(काष्ठा nfp_cpp_explicit *expl,
			   स्थिर काष्ठा nfp_cpp_explicit_command *cmd,
			   u64 address);
पूर्ण;

काष्ठा nfp_cpp *
nfp_cpp_from_operations(स्थिर काष्ठा nfp_cpp_operations *ops,
			काष्ठा device *parent, व्योम *priv);
व्योम *nfp_cpp_priv(काष्ठा nfp_cpp *priv);

पूर्णांक nfp_cpp_area_cache_add(काष्ठा nfp_cpp *cpp, माप_प्रकार size);

/* The following section contains extensions to the
 * NFP CPP API, to be used in a Linux kernel-space context.
 */

/* Use this channel ID क्रम multiple भव channel पूर्णांकerfaces
 * (ie ARM and PCIe) when setting up the पूर्णांकerface field.
 */
#घोषणा NFP_CPP_INTERFACE_CHANNEL_PEROPENER	255
काष्ठा device *nfp_cpp_device(काष्ठा nfp_cpp *cpp);

/* Return code masks क्रम nfp_cpp_explicit_करो()
 */
#घोषणा NFP_SIGNAL_MASK_A	BIT(0)	/* Signal A fired */
#घोषणा NFP_SIGNAL_MASK_B	BIT(1)	/* Signal B fired */

क्रमागत nfp_cpp_explicit_संकेत_mode अणु
	NFP_SIGNAL_NONE = 0,
	NFP_SIGNAL_PUSH = 1,
	NFP_SIGNAL_PUSH_OPTIONAL = -1,
	NFP_SIGNAL_PULL = 2,
	NFP_SIGNAL_PULL_OPTIONAL = -2,
पूर्ण;

काष्ठा nfp_cpp_explicit *nfp_cpp_explicit_acquire(काष्ठा nfp_cpp *cpp);
पूर्णांक nfp_cpp_explicit_set_target(काष्ठा nfp_cpp_explicit *expl, u32 cpp_id,
				u8 len, u8 mask);
पूर्णांक nfp_cpp_explicit_set_data(काष्ठा nfp_cpp_explicit *expl,
			      u8 data_master, u16 data_ref);
पूर्णांक nfp_cpp_explicit_set_संकेत(काष्ठा nfp_cpp_explicit *expl,
				u8 संकेत_master, u8 संकेत_ref);
पूर्णांक nfp_cpp_explicit_set_posted(काष्ठा nfp_cpp_explicit *expl, पूर्णांक posted,
				u8 siga,
				क्रमागत nfp_cpp_explicit_संकेत_mode siga_mode,
				u8 sigb,
				क्रमागत nfp_cpp_explicit_संकेत_mode sigb_mode);
पूर्णांक nfp_cpp_explicit_put(काष्ठा nfp_cpp_explicit *expl,
			 स्थिर व्योम *buff, माप_प्रकार len);
पूर्णांक nfp_cpp_explicit_करो(काष्ठा nfp_cpp_explicit *expl, u64 address);
पूर्णांक nfp_cpp_explicit_get(काष्ठा nfp_cpp_explicit *expl, व्योम *buff, माप_प्रकार len);
व्योम nfp_cpp_explicit_release(काष्ठा nfp_cpp_explicit *expl);
काष्ठा nfp_cpp *nfp_cpp_explicit_cpp(काष्ठा nfp_cpp_explicit *expl);
व्योम *nfp_cpp_explicit_priv(काष्ठा nfp_cpp_explicit *cpp_explicit);

/* Implemented in nfp_cpplib.c */

पूर्णांक nfp_cpp_model_स्वतःdetect(काष्ठा nfp_cpp *cpp, u32 *model);

पूर्णांक nfp_cpp_explicit_पढ़ो(काष्ठा nfp_cpp *cpp, u32 cpp_id,
			  u64 addr, व्योम *buff, माप_प्रकार len,
			  पूर्णांक width_पढ़ो);

पूर्णांक nfp_cpp_explicit_ग_लिखो(काष्ठा nfp_cpp *cpp, u32 cpp_id,
			   u64 addr, स्थिर व्योम *buff, माप_प्रकार len,
			   पूर्णांक width_ग_लिखो);

#पूर्ण_अगर /* !__NFP_CPP_H__ */
