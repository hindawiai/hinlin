<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश "common.h"
#समावेश "pipe.h"

/*
 *		macros
 */
#घोषणा usbhsp_addr_offset(p)	((usbhs_pipe_number(p) - 1) * 2)

#घोषणा usbhsp_flags_set(p, f)	((p)->flags |=  USBHS_PIPE_FLAGS_##f)
#घोषणा usbhsp_flags_clr(p, f)	((p)->flags &= ~USBHS_PIPE_FLAGS_##f)
#घोषणा usbhsp_flags_has(p, f)	((p)->flags &   USBHS_PIPE_FLAGS_##f)
#घोषणा usbhsp_flags_init(p)	करो अणु(p)->flags = 0; पूर्ण जबतक (0)

/*
 * क्रम debug
 */
अटल अक्षर *usbhsp_pipe_name[] = अणु
	[USB_ENDPOINT_XFER_CONTROL]	= "DCP",
	[USB_ENDPOINT_XFER_BULK]	= "BULK",
	[USB_ENDPOINT_XFER_INT]		= "INT",
	[USB_ENDPOINT_XFER_ISOC]	= "ISO",
पूर्ण;

अक्षर *usbhs_pipe_name(काष्ठा usbhs_pipe *pipe)
अणु
	वापस usbhsp_pipe_name[usbhs_pipe_type(pipe)];
पूर्ण

अटल काष्ठा renesas_usbhs_driver_pipe_config
*usbhsp_get_pipe_config(काष्ठा usbhs_priv *priv, पूर्णांक pipe_num)
अणु
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);

	वापस &pipe_configs[pipe_num];
पूर्ण

/*
 *		DCPCTR/PIPEnCTR functions
 */
अटल व्योम usbhsp_pipectrl_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	पूर्णांक offset = usbhsp_addr_offset(pipe);

	अगर (usbhs_pipe_is_dcp(pipe))
		usbhs_bset(priv, DCPCTR, mask, val);
	अन्यथा
		usbhs_bset(priv, PIPEnCTR + offset, mask, val);
पूर्ण

अटल u16 usbhsp_pipectrl_get(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	पूर्णांक offset = usbhsp_addr_offset(pipe);

	अगर (usbhs_pipe_is_dcp(pipe))
		वापस usbhs_पढ़ो(priv, DCPCTR);
	अन्यथा
		वापस usbhs_पढ़ो(priv, PIPEnCTR + offset);
पूर्ण

/*
 *		DCP/PIPE functions
 */
अटल व्योम __usbhsp_pipe_xxx_set(काष्ठा usbhs_pipe *pipe,
				  u16 dcp_reg, u16 pipe_reg,
				  u16 mask, u16 val)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	अगर (usbhs_pipe_is_dcp(pipe))
		usbhs_bset(priv, dcp_reg, mask, val);
	अन्यथा
		usbhs_bset(priv, pipe_reg, mask, val);
पूर्ण

अटल u16 __usbhsp_pipe_xxx_get(काष्ठा usbhs_pipe *pipe,
				 u16 dcp_reg, u16 pipe_reg)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	अगर (usbhs_pipe_is_dcp(pipe))
		वापस usbhs_पढ़ो(priv, dcp_reg);
	अन्यथा
		वापस usbhs_पढ़ो(priv, pipe_reg);
पूर्ण

/*
 *		DCPCFG/PIPECFG functions
 */
अटल व्योम usbhsp_pipe_cfg_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	__usbhsp_pipe_xxx_set(pipe, DCPCFG, PIPECFG, mask, val);
पूर्ण

अटल u16 usbhsp_pipe_cfg_get(काष्ठा usbhs_pipe *pipe)
अणु
	वापस __usbhsp_pipe_xxx_get(pipe, DCPCFG, PIPECFG);
पूर्ण

/*
 *		PIPEnTRN/PIPEnTRE functions
 */
अटल व्योम usbhsp_pipe_trn_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक num = usbhs_pipe_number(pipe);
	u16 reg;

	/*
	 * It is impossible to calculate address,
	 * since PIPEnTRN addresses were mapped अक्रमomly.
	 */
#घोषणा CASE_PIPExTRN(a)		\
	हाल 0x ## a:			\
		reg = PIPE ## a ## TRN;	\
		अवरोध;

	चयन (num) अणु
	CASE_PIPExTRN(1);
	CASE_PIPExTRN(2);
	CASE_PIPExTRN(3);
	CASE_PIPExTRN(4);
	CASE_PIPExTRN(5);
	CASE_PIPExTRN(B);
	CASE_PIPExTRN(C);
	CASE_PIPExTRN(D);
	CASE_PIPExTRN(E);
	CASE_PIPExTRN(F);
	CASE_PIPExTRN(9);
	CASE_PIPExTRN(A);
	शेष:
		dev_err(dev, "unknown pipe (%d)\n", num);
		वापस;
	पूर्ण
	__usbhsp_pipe_xxx_set(pipe, 0, reg, mask, val);
पूर्ण

अटल व्योम usbhsp_pipe_tre_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक num = usbhs_pipe_number(pipe);
	u16 reg;

	/*
	 * It is impossible to calculate address,
	 * since PIPEnTRE addresses were mapped अक्रमomly.
	 */
#घोषणा CASE_PIPExTRE(a)			\
	हाल 0x ## a:				\
		reg = PIPE ## a ## TRE;		\
		अवरोध;

	चयन (num) अणु
	CASE_PIPExTRE(1);
	CASE_PIPExTRE(2);
	CASE_PIPExTRE(3);
	CASE_PIPExTRE(4);
	CASE_PIPExTRE(5);
	CASE_PIPExTRE(B);
	CASE_PIPExTRE(C);
	CASE_PIPExTRE(D);
	CASE_PIPExTRE(E);
	CASE_PIPExTRE(F);
	CASE_PIPExTRE(9);
	CASE_PIPExTRE(A);
	शेष:
		dev_err(dev, "unknown pipe (%d)\n", num);
		वापस;
	पूर्ण

	__usbhsp_pipe_xxx_set(pipe, 0, reg, mask, val);
पूर्ण

/*
 *		PIPEBUF
 */
अटल व्योम usbhsp_pipe_buf_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	अगर (usbhs_pipe_is_dcp(pipe))
		वापस;

	__usbhsp_pipe_xxx_set(pipe, 0, PIPEBUF, mask, val);
पूर्ण

/*
 *		DCPMAXP/PIPEMAXP
 */
अटल व्योम usbhsp_pipe_maxp_set(काष्ठा usbhs_pipe *pipe, u16 mask, u16 val)
अणु
	__usbhsp_pipe_xxx_set(pipe, DCPMAXP, PIPEMAXP, mask, val);
पूर्ण

/*
 *		pipe control functions
 */
अटल व्योम usbhsp_pipe_select(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	/*
	 * On pipe, this is necessary beक्रमe
	 * accesses to below रेजिस्टरs.
	 *
	 * PIPESEL	: usbhsp_pipe_select
	 * PIPECFG	: usbhsp_pipe_cfg_xxx
	 * PIPEBUF	: usbhsp_pipe_buf_xxx
	 * PIPEMAXP	: usbhsp_pipe_maxp_xxx
	 * PIPEPERI
	 */

	/*
	 * अगर pipe is dcp, no pipe is selected.
	 * it is no problem, because dcp have its रेजिस्टर
	 */
	usbhs_ग_लिखो(priv, PIPESEL, 0xF & usbhs_pipe_number(pipe));
पूर्ण

अटल पूर्णांक usbhsp_pipe_barrier(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	पूर्णांक समयout = 1024;
	u16 mask = usbhs_mod_is_host(priv) ? (CSSTS | PID_MASK) : PID_MASK;

	/*
	 * make sure....
	 *
	 * Modअगरy these bits when CSSTS = 0, PID = NAK, and no pipe number is
	 * specअगरied by the CURPIPE bits.
	 * When changing the setting of this bit after changing
	 * the PID bits क्रम the selected pipe from BUF to NAK,
	 * check that CSSTS = 0 and PBUSY = 0.
	 */

	/*
	 * CURPIPE bit = 0
	 *
	 * see also
	 *  "Operation"
	 *  - "Pipe Control"
	 *   - "Pipe Control Registers Switching Procedure"
	 */
	usbhs_ग_लिखो(priv, CFIFOSEL, 0);
	usbhs_pipe_disable(pipe);

	करो अणु
		अगर (!(usbhsp_pipectrl_get(pipe) & mask))
			वापस 0;

		udelay(10);

	पूर्ण जबतक (समयout--);

	वापस -EBUSY;
पूर्ण

पूर्णांक usbhs_pipe_is_accessible(काष्ठा usbhs_pipe *pipe)
अणु
	u16 val;

	val = usbhsp_pipectrl_get(pipe);
	अगर (val & BSTS)
		वापस 0;

	वापस -EBUSY;
पूर्ण

bool usbhs_pipe_contains_transmittable_data(काष्ठा usbhs_pipe *pipe)
अणु
	u16 val;

	/* Do not support क्रम DCP pipe */
	अगर (usbhs_pipe_is_dcp(pipe))
		वापस false;

	val = usbhsp_pipectrl_get(pipe);
	अगर (val & INBUFM)
		वापस true;

	वापस false;
पूर्ण

/*
 *		PID ctrl
 */
अटल व्योम __usbhsp_pid_try_nak_अगर_stall(काष्ठा usbhs_pipe *pipe)
अणु
	u16 pid = usbhsp_pipectrl_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Control Register" - "PID"
	 */
	चयन (pid) अणु
	हाल PID_STALL11:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL10);
		fallthrough;
	हाल PID_STALL10:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_NAK);
	पूर्ण
पूर्ण

व्योम usbhs_pipe_disable(काष्ठा usbhs_pipe *pipe)
अणु
	पूर्णांक समयout = 1024;
	u16 val;

	/* see "Pipe n Control Register" - "PID" */
	__usbhsp_pid_try_nak_अगर_stall(pipe);

	usbhsp_pipectrl_set(pipe, PID_MASK, PID_NAK);

	करो अणु
		val  = usbhsp_pipectrl_get(pipe);
		val &= PBUSY;
		अगर (!val)
			अवरोध;

		udelay(10);
	पूर्ण जबतक (समयout--);
पूर्ण

व्योम usbhs_pipe_enable(काष्ठा usbhs_pipe *pipe)
अणु
	/* see "Pipe n Control Register" - "PID" */
	__usbhsp_pid_try_nak_अगर_stall(pipe);

	usbhsp_pipectrl_set(pipe, PID_MASK, PID_BUF);
पूर्ण

व्योम usbhs_pipe_stall(काष्ठा usbhs_pipe *pipe)
अणु
	u16 pid = usbhsp_pipectrl_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Control Register" - "PID"
	 */
	चयन (pid) अणु
	हाल PID_NAK:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL10);
		अवरोध;
	हाल PID_BUF:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL11);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक usbhs_pipe_is_stall(काष्ठा usbhs_pipe *pipe)
अणु
	u16 pid = usbhsp_pipectrl_get(pipe) & PID_MASK;

	वापस (पूर्णांक)(pid == PID_STALL10 || pid == PID_STALL11);
पूर्ण

व्योम usbhs_pipe_set_trans_count_अगर_bulk(काष्ठा usbhs_pipe *pipe, पूर्णांक len)
अणु
	अगर (!usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		वापस;

	/*
	 * clear and disable transfer counter क्रम IN/OUT pipe
	 */
	usbhsp_pipe_tre_set(pipe, TRCLR | TRENB, TRCLR);

	/*
	 * Only IN direction bulk pipe can use transfer count.
	 * Without using this function,
	 * received data will अवरोध अगर it was large data size.
	 * see PIPEnTRN/PIPEnTRE क्रम detail
	 */
	अगर (usbhs_pipe_is_dir_in(pipe)) अणु
		पूर्णांक maxp = usbhs_pipe_get_maxpacket(pipe);

		usbhsp_pipe_trn_set(pipe, 0xffff, DIV_ROUND_UP(len, maxp));
		usbhsp_pipe_tre_set(pipe, TRENB, TRENB); /* enable */
	पूर्ण
पूर्ण


/*
 *		pipe setup
 */
अटल पूर्णांक usbhsp_setup_pipecfg(काष्ठा usbhs_pipe *pipe, पूर्णांक is_host,
				पूर्णांक dir_in, u16 *pipecfg)
अणु
	u16 type = 0;
	u16 bfre = 0;
	u16 dblb = 0;
	u16 cnपंचांगd = 0;
	u16 dir = 0;
	u16 epnum = 0;
	u16 shtnak = 0;
	अटल स्थिर u16 type_array[] = अणु
		[USB_ENDPOINT_XFER_BULK] = TYPE_BULK,
		[USB_ENDPOINT_XFER_INT]  = TYPE_INT,
		[USB_ENDPOINT_XFER_ISOC] = TYPE_ISO,
	पूर्ण;

	अगर (usbhs_pipe_is_dcp(pipe))
		वापस -EINVAL;

	/*
	 * PIPECFG
	 *
	 * see
	 *  - "Register Descriptions" - "PIPECFG" रेजिस्टर
	 *  - "Features"  - "Pipe configuration"
	 *  - "Operation" - "Pipe Control"
	 */

	/* TYPE */
	type = type_array[usbhs_pipe_type(pipe)];

	/* BFRE */
	अगर (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		bfre = 0; /* FIXME */

	/* DBLB: see usbhs_pipe_config_update() */

	/* CNTMD */
	अगर (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		cnपंचांगd = 0; /* FIXME */

	/* सूची */
	अगर (dir_in)
		usbhsp_flags_set(pipe, IS_सूची_HOST);

	अगर (!!is_host ^ !!dir_in)
		dir |= सूची_OUT;

	अगर (!dir)
		usbhsp_flags_set(pipe, IS_सूची_IN);

	/* SHTNAK */
	अगर (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK) &&
	    !dir)
		shtnak = SHTNAK;

	/* EPNUM */
	epnum = 0; /* see usbhs_pipe_config_update() */
	*pipecfg = type		|
		   bfre		|
		   dblb		|
		   cnपंचांगd	|
		   dir		|
		   shtnak	|
		   epnum;
	वापस 0;
पूर्ण

अटल u16 usbhsp_setup_pipebuff(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक pipe_num = usbhs_pipe_number(pipe);
	u16 buff_size;
	u16 bufnmb;
	u16 bufnmb_cnt;
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_config =
					usbhsp_get_pipe_config(priv, pipe_num);

	/*
	 * PIPEBUF
	 *
	 * see
	 *  - "Register Descriptions" - "PIPEBUF" रेजिस्टर
	 *  - "Features"  - "Pipe configuration"
	 *  - "Operation" - "FIFO Buffer Memory"
	 *  - "Operation" - "Pipe Control"
	 */
	buff_size = pipe_config->bufsize;
	bufnmb = pipe_config->bufnum;

	/* change buff_size to रेजिस्टर value */
	bufnmb_cnt = (buff_size / 64) - 1;

	dev_dbg(dev, "pipe : %d : buff_size 0x%x: bufnmb 0x%x\n",
		pipe_num, buff_size, bufnmb);

	वापस	(0x1f & bufnmb_cnt)	<< 10 |
		(0xff & bufnmb)		<<  0;
पूर्ण

व्योम usbhs_pipe_config_update(काष्ठा usbhs_pipe *pipe, u16 devsel,
			      u16 epnum, u16 maxp)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	पूर्णांक pipe_num = usbhs_pipe_number(pipe);
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_config =
					usbhsp_get_pipe_config(priv, pipe_num);
	u16 dblb = pipe_config->द्विगुन_buf ? DBLB : 0;

	अगर (devsel > 0xA) अणु
		काष्ठा device *dev = usbhs_priv_to_dev(priv);

		dev_err(dev, "devsel error %d\n", devsel);

		devsel = 0;
	पूर्ण

	usbhsp_pipe_barrier(pipe);

	pipe->maxp = maxp;

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_maxp_set(pipe, 0xFFFF,
			     (devsel << 12) |
			     maxp);

	अगर (!usbhs_pipe_is_dcp(pipe))
		usbhsp_pipe_cfg_set(pipe,  0x000F | DBLB, epnum | dblb);
पूर्ण

/*
 *		pipe control
 */
पूर्णांक usbhs_pipe_get_maxpacket(काष्ठा usbhs_pipe *pipe)
अणु
	/*
	 * see
	 *	usbhs_pipe_config_update()
	 *	usbhs_dcp_दो_स्मृति()
	 */
	वापस pipe->maxp;
पूर्ण

पूर्णांक usbhs_pipe_is_dir_in(काष्ठा usbhs_pipe *pipe)
अणु
	वापस usbhsp_flags_has(pipe, IS_सूची_IN);
पूर्ण

पूर्णांक usbhs_pipe_is_dir_host(काष्ठा usbhs_pipe *pipe)
अणु
	वापस usbhsp_flags_has(pipe, IS_सूची_HOST);
पूर्ण

पूर्णांक usbhs_pipe_is_running(काष्ठा usbhs_pipe *pipe)
अणु
	वापस usbhsp_flags_has(pipe, IS_RUNNING);
पूर्ण

व्योम usbhs_pipe_running(काष्ठा usbhs_pipe *pipe, पूर्णांक running)
अणु
	अगर (running)
		usbhsp_flags_set(pipe, IS_RUNNING);
	अन्यथा
		usbhsp_flags_clr(pipe, IS_RUNNING);
पूर्ण

व्योम usbhs_pipe_data_sequence(काष्ठा usbhs_pipe *pipe, पूर्णांक sequence)
अणु
	u16 mask = (SQCLR | SQSET);
	u16 val;

	/*
	 * sequence
	 *  0  : data0
	 *  1  : data1
	 *  -1 : no change
	 */
	चयन (sequence) अणु
	हाल 0:
		val = SQCLR;
		अवरोध;
	हाल 1:
		val = SQSET;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	usbhsp_pipectrl_set(pipe, mask, val);
पूर्ण

अटल पूर्णांक usbhs_pipe_get_data_sequence(काष्ठा usbhs_pipe *pipe)
अणु
	वापस !!(usbhsp_pipectrl_get(pipe) & SQMON);
पूर्ण

व्योम usbhs_pipe_clear(काष्ठा usbhs_pipe *pipe)
अणु
	अगर (usbhs_pipe_is_dcp(pipe)) अणु
		usbhs_fअगरo_clear_dcp(pipe);
	पूर्ण अन्यथा अणु
		usbhsp_pipectrl_set(pipe, ACLRM, ACLRM);
		usbhsp_pipectrl_set(pipe, ACLRM, 0);
	पूर्ण
पूर्ण

/* Should call usbhsp_pipe_select() beक्रमe */
व्योम usbhs_pipe_clear_without_sequence(काष्ठा usbhs_pipe *pipe,
				       पूर्णांक needs_bfre, पूर्णांक bfre_enable)
अणु
	पूर्णांक sequence;

	usbhsp_pipe_select(pipe);
	sequence = usbhs_pipe_get_data_sequence(pipe);
	अगर (needs_bfre)
		usbhsp_pipe_cfg_set(pipe, BFRE, bfre_enable ? BFRE : 0);
	usbhs_pipe_clear(pipe);
	usbhs_pipe_data_sequence(pipe, sequence);
पूर्ण

व्योम usbhs_pipe_config_change_bfre(काष्ठा usbhs_pipe *pipe, पूर्णांक enable)
अणु
	अगर (usbhs_pipe_is_dcp(pipe))
		वापस;

	usbhsp_pipe_select(pipe);
	/* check अगर the driver needs to change the BFRE value */
	अगर (!(enable ^ !!(usbhsp_pipe_cfg_get(pipe) & BFRE)))
		वापस;

	usbhs_pipe_clear_without_sequence(pipe, 1, enable);
पूर्ण

अटल काष्ठा usbhs_pipe *usbhsp_get_pipe(काष्ठा usbhs_priv *priv, u32 type)
अणु
	काष्ठा usbhs_pipe *pos, *pipe;
	पूर्णांक i;

	/*
	 * find target pipe
	 */
	pipe = शून्य;
	usbhs_क्रम_each_pipe_with_dcp(pos, priv, i) अणु
		अगर (!usbhs_pipe_type_is(pos, type))
			जारी;
		अगर (usbhsp_flags_has(pos, IS_USED))
			जारी;

		pipe = pos;
		अवरोध;
	पूर्ण

	अगर (!pipe)
		वापस शून्य;

	/*
	 * initialize pipe flags
	 */
	usbhsp_flags_init(pipe);
	usbhsp_flags_set(pipe, IS_USED);

	वापस pipe;
पूर्ण

अटल व्योम usbhsp_put_pipe(काष्ठा usbhs_pipe *pipe)
अणु
	usbhsp_flags_init(pipe);
पूर्ण

व्योम usbhs_pipe_init(काष्ठा usbhs_priv *priv,
		     पूर्णांक (*dma_map_ctrl)(काष्ठा device *dma_dev,
					 काष्ठा usbhs_pkt *pkt, पूर्णांक map))
अणु
	काष्ठा usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
	काष्ठा usbhs_pipe *pipe;
	पूर्णांक i;

	usbhs_क्रम_each_pipe_with_dcp(pipe, priv, i) अणु
		usbhsp_flags_init(pipe);
		pipe->fअगरo = शून्य;
		pipe->mod_निजी = शून्य;
		INIT_LIST_HEAD(&pipe->list);

		/* pipe क्रमce init */
		usbhs_pipe_clear(pipe);
	पूर्ण

	info->dma_map_ctrl = dma_map_ctrl;
पूर्ण

काष्ठा usbhs_pipe *usbhs_pipe_दो_स्मृति(काष्ठा usbhs_priv *priv,
				     पूर्णांक endpoपूर्णांक_type,
				     पूर्णांक dir_in)
अणु
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usbhs_pipe *pipe;
	पूर्णांक is_host = usbhs_mod_is_host(priv);
	पूर्णांक ret;
	u16 pipecfg, pipebuf;

	pipe = usbhsp_get_pipe(priv, endpoपूर्णांक_type);
	अगर (!pipe) अणु
		dev_err(dev, "can't get pipe (%s)\n",
			usbhsp_pipe_name[endpoपूर्णांक_type]);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&pipe->list);

	usbhs_pipe_disable(pipe);

	/* make sure pipe is not busy */
	ret = usbhsp_pipe_barrier(pipe);
	अगर (ret < 0) अणु
		dev_err(dev, "pipe setup failed %d\n", usbhs_pipe_number(pipe));
		वापस शून्य;
	पूर्ण

	अगर (usbhsp_setup_pipecfg(pipe, is_host, dir_in, &pipecfg)) अणु
		dev_err(dev, "can't setup pipe\n");
		वापस शून्य;
	पूर्ण

	pipebuf  = usbhsp_setup_pipebuff(pipe);

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, pipecfg);
	usbhsp_pipe_buf_set(pipe, 0xFFFF, pipebuf);
	usbhs_pipe_clear(pipe);

	usbhs_pipe_sequence_data0(pipe);

	dev_dbg(dev, "enable pipe %d : %s (%s)\n",
		usbhs_pipe_number(pipe),
		usbhs_pipe_name(pipe),
		usbhs_pipe_is_dir_in(pipe) ? "in" : "out");

	/*
	 * epnum / maxp are still not set to this pipe.
	 * call usbhs_pipe_config_update() after this function !!
	 */

	वापस pipe;
पूर्ण

व्योम usbhs_pipe_मुक्त(काष्ठा usbhs_pipe *pipe)
अणु
	usbhsp_pipe_select(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, 0);
	usbhsp_put_pipe(pipe);
पूर्ण

व्योम usbhs_pipe_select_fअगरo(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_fअगरo *fअगरo)
अणु
	अगर (pipe->fअगरo)
		pipe->fअगरo->pipe = शून्य;

	pipe->fअगरo = fअगरo;

	अगर (fअगरo)
		fअगरo->pipe = pipe;
पूर्ण


/*
 *		dcp control
 */
काष्ठा usbhs_pipe *usbhs_dcp_दो_स्मृति(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_pipe *pipe;

	pipe = usbhsp_get_pipe(priv, USB_ENDPOINT_XFER_CONTROL);
	अगर (!pipe)
		वापस शून्य;

	INIT_LIST_HEAD(&pipe->list);

	/*
	 * call usbhs_pipe_config_update() after this function !!
	 */

	वापस pipe;
पूर्ण

व्योम usbhs_dcp_control_transfer_करोne(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	WARN_ON(!usbhs_pipe_is_dcp(pipe));

	usbhs_pipe_enable(pipe);

	अगर (!usbhs_mod_is_host(priv)) /* funconly */
		usbhsp_pipectrl_set(pipe, CCPL, CCPL);
पूर्ण

व्योम usbhs_dcp_dir_क्रम_host(काष्ठा usbhs_pipe *pipe, पूर्णांक dir_out)
अणु
	usbhsp_pipe_cfg_set(pipe, सूची_OUT,
			    dir_out ? सूची_OUT : 0);
पूर्ण

/*
 *		pipe module function
 */
पूर्णांक usbhs_pipe_probe(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
	काष्ठा usbhs_pipe *pipe;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);
	पूर्णांक pipe_size = usbhs_get_dparam(priv, pipe_size);
	पूर्णांक i;

	/* This driver expects 1st pipe is DCP */
	अगर (pipe_configs[0].type != USB_ENDPOINT_XFER_CONTROL) अणु
		dev_err(dev, "1st PIPE is not DCP\n");
		वापस -EINVAL;
	पूर्ण

	info->pipe = kसुस्मृति(pipe_size, माप(काष्ठा usbhs_pipe),
			     GFP_KERNEL);
	अगर (!info->pipe)
		वापस -ENOMEM;

	info->size = pipe_size;

	/*
	 * init pipe
	 */
	usbhs_क्रम_each_pipe_with_dcp(pipe, priv, i) अणु
		pipe->priv = priv;

		usbhs_pipe_type(pipe) =
			pipe_configs[i].type & USB_ENDPOINT_XFERTYPE_MASK;

		dev_dbg(dev, "pipe %x\t: %s\n",
			i, usbhsp_pipe_name[pipe_configs[i].type]);
	पूर्ण

	वापस 0;
पूर्ण

व्योम usbhs_pipe_हटाओ(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);

	kमुक्त(info->pipe);
पूर्ण
