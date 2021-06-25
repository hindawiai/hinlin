<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    tuner-i2c.h - i2c पूर्णांकerface क्रम dअगरferent tuners

    Copyright (C) 2007 Michael Krufky (mkrufky@linuxtv.org)

*/

#अगर_अघोषित __TUNER_I2C_H__
#घोषणा __TUNER_I2C_H__

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

काष्ठा tuner_i2c_props अणु
	u8 addr;
	काष्ठा i2c_adapter *adap;

	/* used क्रम tuner instance management */
	पूर्णांक count;
	अक्षर *name;
पूर्ण;

अटल अंतरभूत पूर्णांक tuner_i2c_xfer_send(काष्ठा tuner_i2c_props *props,
				      अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = props->addr, .flags = 0,
			       .buf = buf, .len = len पूर्ण;
	पूर्णांक ret = i2c_transfer(props->adap, &msg, 1);

	वापस (ret == 1) ? len : ret;
पूर्ण

अटल अंतरभूत पूर्णांक tuner_i2c_xfer_recv(काष्ठा tuner_i2c_props *props,
				      अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = props->addr, .flags = I2C_M_RD,
			       .buf = buf, .len = len पूर्ण;
	पूर्णांक ret = i2c_transfer(props->adap, &msg, 1);

	वापस (ret == 1) ? len : ret;
पूर्ण

अटल अंतरभूत पूर्णांक tuner_i2c_xfer_send_recv(काष्ठा tuner_i2c_props *props,
					   अचिन्हित अक्षर *obuf, पूर्णांक olen,
					   अचिन्हित अक्षर *ibuf, पूर्णांक ilen)
अणु
	काष्ठा i2c_msg msg[2] = अणु अणु .addr = props->addr, .flags = 0,
				    .buf = obuf, .len = olen पूर्ण,
				  अणु .addr = props->addr, .flags = I2C_M_RD,
				    .buf = ibuf, .len = ilen पूर्ण पूर्ण;
	पूर्णांक ret = i2c_transfer(props->adap, msg, 2);

	वापस (ret == 2) ? ilen : ret;
पूर्ण

/* Callers must declare as a global क्रम the module:
 *
 * अटल LIST_HEAD(hybrid_tuner_instance_list);
 *
 * hybrid_tuner_instance_list should be the third argument
 * passed पूर्णांकo hybrid_tuner_request_state().
 *
 * state काष्ठाure must contain the following:
 *
 *	काष्ठा list_head	hybrid_tuner_instance_list;
 *	काष्ठा tuner_i2c_props	i2c_props;
 *
 * hybrid_tuner_instance_list (both within state काष्ठाure and globally)
 * is only required अगर the driver is using hybrid_tuner_request_state
 * and hybrid_tuner_release_state to manage state sharing between
 * multiple instances of hybrid tuners.
 */

#घोषणा tuner_prपूर्णांकk(kernlvl, i2cprops, fmt, arg...) करो अणु		\
	prपूर्णांकk(kernlvl "%s %d-%04x: " fmt, i2cprops.name,		\
			i2cprops.adap ?					\
				i2c_adapter_id(i2cprops.adap) : -1,	\
			i2cprops.addr, ##arg);				\
	 पूर्ण जबतक (0)

/* TO DO: convert all callers of these macros to pass in
 * काष्ठा tuner_i2c_props, then हटाओ the macro wrappers */

#घोषणा __tuner_warn(i2cprops, fmt, arg...) करो अणु			\
	tuner_prपूर्णांकk(KERN_WARNING, i2cprops, fmt, ##arg);		\
	पूर्ण जबतक (0)

#घोषणा __tuner_info(i2cprops, fmt, arg...) करो अणु			\
	tuner_prपूर्णांकk(KERN_INFO, i2cprops, fmt, ##arg);			\
	पूर्ण जबतक (0)

#घोषणा __tuner_err(i2cprops, fmt, arg...) करो अणु				\
	tuner_prपूर्णांकk(KERN_ERR, i2cprops, fmt, ##arg);			\
	पूर्ण जबतक (0)

#घोषणा __tuner_dbg(i2cprops, fmt, arg...) करो अणु				\
	अगर ((debug))							\
		tuner_prपूर्णांकk(KERN_DEBUG, i2cprops, fmt, ##arg);		\
	पूर्ण जबतक (0)

#घोषणा tuner_warn(fmt, arg...) __tuner_warn(priv->i2c_props, fmt, ##arg)
#घोषणा tuner_info(fmt, arg...) __tuner_info(priv->i2c_props, fmt, ##arg)
#घोषणा tuner_err(fmt, arg...) __tuner_err(priv->i2c_props, fmt, ##arg)
#घोषणा tuner_dbg(fmt, arg...) __tuner_dbg(priv->i2c_props, fmt, ##arg)

/****************************************************************************/

/* The वापस value of hybrid_tuner_request_state indicates the number of
 * instances using this tuner object.
 *
 * 0 - no instances, indicates an error - kzalloc must have failed
 *
 * 1 - one instance, indicates that the tuner object was created successfully
 *
 * 2 (or more) instances, indicates that an existing tuner object was found
 */

#घोषणा hybrid_tuner_request_state(type, state, list, i2cadap, i2caddr, devname)\
(अणु									\
	पूर्णांक __ret = 0;							\
	list_क्रम_each_entry(state, &list, hybrid_tuner_instance_list) अणु	\
		अगर (((i2cadap) && (state->i2c_props.adap)) &&		\
		    ((i2c_adapter_id(state->i2c_props.adap) ==		\
		      i2c_adapter_id(i2cadap)) &&			\
		     (i2caddr == state->i2c_props.addr))) अणु		\
			__tuner_info(state->i2c_props,			\
				     "attaching existing instance\n");	\
			state->i2c_props.count++;			\
			__ret = state->i2c_props.count;			\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	अगर (0 == __ret) अणु						\
		state = kzalloc(माप(type), GFP_KERNEL);		\
		अगर (!state) अणु						\
			__ret = -ENOMEM;				\
			जाओ __fail;					\
		पूर्ण							\
		state->i2c_props.addr = i2caddr;			\
		state->i2c_props.adap = i2cadap;			\
		state->i2c_props.name = devname;			\
		__tuner_info(state->i2c_props,				\
			     "creating new instance\n");		\
		list_add_tail(&state->hybrid_tuner_instance_list, &list);\
		state->i2c_props.count++;				\
		__ret = state->i2c_props.count;				\
	पूर्ण								\
__fail:									\
	__ret;								\
पूर्ण)

#घोषणा hybrid_tuner_release_state(state)				\
(अणु									\
	पूर्णांक __ret;							\
	state->i2c_props.count--;					\
	__ret = state->i2c_props.count;					\
	अगर (!state->i2c_props.count) अणु					\
		__tuner_info(state->i2c_props, "destroying instance\n");\
		list_del(&state->hybrid_tuner_instance_list);		\
		kमुक्त(state);						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा hybrid_tuner_report_instance_count(state)			\
(अणु									\
	पूर्णांक __ret = 0;							\
	अगर (state)							\
		__ret = state->i2c_props.count;				\
	__ret;								\
पूर्ण)

#पूर्ण_अगर /* __TUNER_I2C_H__ */
