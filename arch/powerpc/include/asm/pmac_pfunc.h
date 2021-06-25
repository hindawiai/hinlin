<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PMAC_PFUNC_H__
#घोषणा __PMAC_PFUNC_H__

#समावेश <linux/types.h>
#समावेश <linux/list.h>

/* Flags in command lists */
#घोषणा PMF_FLAGS_ON_INIT		0x80000000u
#घोषणा PMF_FLGAS_ON_TERM		0x40000000u
#घोषणा PMF_FLAGS_ON_SLEEP		0x20000000u
#घोषणा PMF_FLAGS_ON_WAKE		0x10000000u
#घोषणा PMF_FLAGS_ON_DEMAND		0x08000000u
#घोषणा PMF_FLAGS_INT_GEN		0x04000000u
#घोषणा PMF_FLAGS_HIGH_SPEED		0x02000000u
#घोषणा PMF_FLAGS_LOW_SPEED		0x01000000u
#घोषणा PMF_FLAGS_SIDE_EFFECTS		0x00800000u

/*
 * Arguments to a platक्रमm function call.
 *
 * NOTE: By convention, poपूर्णांकer arguments poपूर्णांक to an u32
 */
काष्ठा pmf_args अणु
	जोड़ अणु
		u32 v;
		u32 *p;
	पूर्ण u[4];
	अचिन्हित पूर्णांक count;
पूर्ण;

/*
 * A driver capable of पूर्णांकerpreting commands provides a handlers
 * काष्ठाure filled with whatever handlers are implemented by this
 * driver. Non implemented handlers are left शून्य.
 *
 * PMF_STD_ARGS are the same arguments that are passed to the parser
 * and that माला_लो passed back to the various handlers.
 *
 * Interpreting a given function always start with a begin() call which
 * वापसs an instance data to be passed around subsequent calls, and
 * ends with an end() call. This allows the low level driver to implement
 * locking policy or per-function instance data.
 *
 * For पूर्णांकerrupt capable functions, irq_enable() is called when a client
 * रेजिस्टरs, and irq_disable() is called when the last client unरेजिस्टरs
 * Note that irq_enable & irq_disable are called within a semaphore held
 * by the core, thus you should not try to रेजिस्टर yourself to some other
 * pmf पूर्णांकerrupt during those calls.
 */

#घोषणा PMF_STD_ARGS	काष्ठा pmf_function *func, व्योम *instdata, \
		        काष्ठा pmf_args *args

काष्ठा pmf_function;

काष्ठा pmf_handlers अणु
	व्योम * (*begin)(काष्ठा pmf_function *func, काष्ठा pmf_args *args);
	व्योम (*end)(काष्ठा pmf_function *func, व्योम *instdata);

	पूर्णांक (*irq_enable)(काष्ठा pmf_function *func);
	पूर्णांक (*irq_disable)(काष्ठा pmf_function *func);

	पूर्णांक (*ग_लिखो_gpio)(PMF_STD_ARGS, u8 value, u8 mask);
	पूर्णांक (*पढ़ो_gpio)(PMF_STD_ARGS, u8 mask, पूर्णांक rshअगरt, u8 xor);

	पूर्णांक (*ग_लिखो_reg32)(PMF_STD_ARGS, u32 offset, u32 value, u32 mask);
	पूर्णांक (*पढ़ो_reg32)(PMF_STD_ARGS, u32 offset);
	पूर्णांक (*ग_लिखो_reg16)(PMF_STD_ARGS, u32 offset, u16 value, u16 mask);
	पूर्णांक (*पढ़ो_reg16)(PMF_STD_ARGS, u32 offset);
	पूर्णांक (*ग_लिखो_reg8)(PMF_STD_ARGS, u32 offset, u8 value, u8 mask);
	पूर्णांक (*पढ़ो_reg8)(PMF_STD_ARGS, u32 offset);

	पूर्णांक (*delay)(PMF_STD_ARGS, u32 duration);

	पूर्णांक (*रुको_reg32)(PMF_STD_ARGS, u32 offset, u32 value, u32 mask);
	पूर्णांक (*रुको_reg16)(PMF_STD_ARGS, u32 offset, u16 value, u16 mask);
	पूर्णांक (*रुको_reg8)(PMF_STD_ARGS, u32 offset, u8 value, u8 mask);

	पूर्णांक (*पढ़ो_i2c)(PMF_STD_ARGS, u32 len);
	पूर्णांक (*ग_लिखो_i2c)(PMF_STD_ARGS, u32 len, स्थिर u8 *data);
	पूर्णांक (*rmw_i2c)(PMF_STD_ARGS, u32 masklen, u32 valuelen, u32 totallen,
		       स्थिर u8 *maskdata, स्थिर u8 *valuedata);

	पूर्णांक (*पढ़ो_cfg)(PMF_STD_ARGS, u32 offset, u32 len);
	पूर्णांक (*ग_लिखो_cfg)(PMF_STD_ARGS, u32 offset, u32 len, स्थिर u8 *data);
	पूर्णांक (*rmw_cfg)(PMF_STD_ARGS, u32 offset, u32 masklen, u32 valuelen,
		       u32 totallen, स्थिर u8 *maskdata, स्थिर u8 *valuedata);

	पूर्णांक (*पढ़ो_i2c_sub)(PMF_STD_ARGS, u8 subaddr, u32 len);
	पूर्णांक (*ग_लिखो_i2c_sub)(PMF_STD_ARGS, u8 subaddr, u32 len, स्थिर u8 *data);
	पूर्णांक (*set_i2c_mode)(PMF_STD_ARGS, पूर्णांक mode);
	पूर्णांक (*rmw_i2c_sub)(PMF_STD_ARGS, u8 subaddr, u32 masklen, u32 valuelen,
			   u32 totallen, स्थिर u8 *maskdata,
			   स्थिर u8 *valuedata);

	पूर्णांक (*पढ़ो_reg32_msrx)(PMF_STD_ARGS, u32 offset, u32 mask, u32 shअगरt,
			       u32 xor);
	पूर्णांक (*पढ़ो_reg16_msrx)(PMF_STD_ARGS, u32 offset, u32 mask, u32 shअगरt,
			       u32 xor);
	पूर्णांक (*पढ़ो_reg8_msrx)(PMF_STD_ARGS, u32 offset, u32 mask, u32 shअगरt,
			      u32 xor);

	पूर्णांक (*ग_लिखो_reg32_slm)(PMF_STD_ARGS, u32 offset, u32 shअगरt, u32 mask);
	पूर्णांक (*ग_लिखो_reg16_slm)(PMF_STD_ARGS, u32 offset, u32 shअगरt, u32 mask);
	पूर्णांक (*ग_लिखो_reg8_slm)(PMF_STD_ARGS, u32 offset, u32 shअगरt, u32 mask);

	पूर्णांक (*mask_and_compare)(PMF_STD_ARGS, u32 len, स्थिर u8 *maskdata,
				स्थिर u8 *valuedata);

	काष्ठा module *owner;
पूर्ण;


/*
 * Drivers who expose platक्रमm functions रेजिस्टर at init समय, this
 * causes the platक्रमm functions क्रम that device node to be parsed in
 * advance and associated with the device. The data काष्ठाures are
 * partially खुला so a driver can walk the list of platक्रमm functions
 * and eventually inspect the flags
 */
काष्ठा pmf_device;

काष्ठा pmf_function अणु
	/* All functions क्रम a given driver are linked */
	काष्ठा list_head	link;

	/* Function node & driver data */
	काष्ठा device_node	*node;
	व्योम			*driver_data;

	/* For पूर्णांकernal use by core */
	काष्ठा pmf_device	*dev;

	/* The name is the "xxx" in "platform-do-xxx", this is how
	 * platक्रमm functions are identअगरied by this code. Some functions
	 * only operate क्रम a given target, in which हाल the phandle is
	 * here (or 0 अगर the filter करोesn't apply)
	 */
	स्थिर अक्षर		*name;
	u32			phandle;

	/* The flags क्रम that function. You can have several functions
	 * with the same name and dअगरferent flag
	 */
	u32			flags;

	/* The actual tokenized function blob */
	स्थिर व्योम		*data;
	अचिन्हित पूर्णांक		length;

	/* Interrupt clients */
	काष्ठा list_head	irq_clients;

	/* Refcounting */
	काष्ठा kref		ref;
पूर्ण;

/*
 * For platक्रमm functions that are पूर्णांकerrupts, one can रेजिस्टर
 * irq_client काष्ठाures. You canNOT use the same काष्ठाure twice
 * as it contains a link member. Also, the callback is called with
 * a spinlock held, you must not call back पूर्णांकo any of the pmf_* functions
 * from within that callback
 */
काष्ठा pmf_irq_client अणु
	व्योम			(*handler)(व्योम *data);
	व्योम			*data;
	काष्ठा module		*owner;
	काष्ठा list_head	link;
	काष्ठा pmf_function	*func;
पूर्ण;


/*
 * Register/Unरेजिस्टर a function-capable driver and its handlers
 */
बाह्य पूर्णांक pmf_रेजिस्टर_driver(काष्ठा device_node *np,
			      काष्ठा pmf_handlers *handlers,
			      व्योम *driverdata);

बाह्य व्योम pmf_unरेजिस्टर_driver(काष्ठा device_node *np);


/*
 * Register/Unरेजिस्टर पूर्णांकerrupt clients
 */
बाह्य पूर्णांक pmf_रेजिस्टर_irq_client(काष्ठा device_node *np,
				   स्थिर अक्षर *name,
				   काष्ठा pmf_irq_client *client);

बाह्य व्योम pmf_unरेजिस्टर_irq_client(काष्ठा pmf_irq_client *client);

/*
 * Called by the handlers when an irq happens
 */
बाह्य व्योम pmf_करो_irq(काष्ठा pmf_function *func);


/*
 * Low level call to platक्रमm functions.
 *
 * The phandle can filter on the target object क्रम functions that have
 * multiple tarमाला_लो, the flags allow you to restrict the call to a given
 * combination of flags.
 *
 * The args array contains as many arguments as is required by the function,
 * this is dependent on the function you are calling, unक्रमtunately Apple
 * mechanism provides no way to encode that so you have to get it right at
 * the call site. Some functions require no args, in which हाल, you can
 * pass शून्य.
 *
 * You can also pass शून्य to the name. This will match any function that has
 * the appropriate combination of flags & phandle or you can pass 0 to the
 * phandle to match any
 */
बाह्य पूर्णांक pmf_करो_functions(काष्ठा device_node *np, स्थिर अक्षर *name,
			    u32 phandle, u32 flags, काष्ठा pmf_args *args);



/*
 * High level call to a platक्रमm function.
 *
 * This one looks क्रम the platक्रमm-xxx first so you should call it to the
 * actual target अगर any. It will fallback to platक्रमm-करो-xxx अगर it can't
 * find one. It will also exclusively target functions that have
 * the "OnDemand" flag.
 */

बाह्य पूर्णांक pmf_call_function(काष्ठा device_node *target, स्थिर अक्षर *name,
			     काष्ठा pmf_args *args);


/*
 * For low latency पूर्णांकerrupt usage, you can lookup क्रम on-demand functions
 * using the functions below
 */

बाह्य काष्ठा pmf_function *pmf_find_function(काष्ठा device_node *target,
					      स्थिर अक्षर *name);

बाह्य काष्ठा pmf_function * pmf_get_function(काष्ठा pmf_function *func);
बाह्य व्योम pmf_put_function(काष्ठा pmf_function *func);

बाह्य पूर्णांक pmf_call_one(काष्ठा pmf_function *func, काष्ठा pmf_args *args);

पूर्णांक pmac_pfunc_base_install(व्योम);

/* Suspend/resume code called by via-pmu directly क्रम now */
बाह्य व्योम pmac_pfunc_base_suspend(व्योम);
बाह्य व्योम pmac_pfunc_base_resume(व्योम);

#पूर्ण_अगर /* __PMAC_PFUNC_H__ */
