<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A framebuffer driver क्रम VBE 2.0+ compliant video cards
 *
 * (c) 2007 Michal Januszewski <spock@gentoo.org>
 *     Loosely based upon the vesafb driver.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/connector.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <video/edid.h>
#समावेश <video/uvesafb.h>
#अगर_घोषित CONFIG_X86
#समावेश <video/vga.h>
#पूर्ण_अगर
#समावेश "edid.h"

अटल काष्ठा cb_id uvesafb_cn_id = अणु
	.idx = CN_IDX_V86D,
	.val = CN_VAL_V86D_UVESAFB
पूर्ण;
अटल अक्षर v86d_path[PATH_MAX] = "/sbin/v86d";
अटल अक्षर v86d_started;	/* has v86d been started by uvesafb? */

अटल स्थिर काष्ठा fb_fix_screeninfo uvesafb_fix = अणु
	.id	= "VESA VGA",
	.type	= FB_TYPE_PACKED_PIXELS,
	.accel	= FB_ACCEL_NONE,
	.visual = FB_VISUAL_TRUECOLOR,
पूर्ण;

अटल पूर्णांक mtrr		= 3;	/* enable mtrr by शेष */
अटल bool blank	= true;	/* enable blanking by शेष */
अटल पूर्णांक ypan		= 1;	/* 0: scroll, 1: ypan, 2: ywrap */
अटल bool pmi_setpal	= true; /* use PMI क्रम palette changes */
अटल bool nocrtc;		/* ignore CRTC settings */
अटल bool noedid;		/* करोn't try DDC transfers */
अटल पूर्णांक vram_remap;		/* set amt. of memory to be used */
अटल पूर्णांक vram_total;		/* set total amount of memory */
अटल u16 maxclk;		/* maximum pixel घड़ी */
अटल u16 maxvf;		/* maximum vertical frequency */
अटल u16 maxhf;		/* maximum horizontal frequency */
अटल u16 vbemode;		/* क्रमce use of a specअगरic VBE mode */
अटल अक्षर *mode_option;
अटल u8  dac_width	= 6;

अटल काष्ठा uvesafb_ktask *uvfb_tasks[UVESAFB_TASKS_MAX];
अटल DEFINE_MUTEX(uvfb_lock);

/*
 * A handler क्रम replies from userspace.
 *
 * Make sure each message passes consistency checks and अगर it करोes,
 * find the kernel part of the task काष्ठा, copy the रेजिस्टरs and
 * the buffer contents and then complete the task.
 */
अटल व्योम uvesafb_cn_callback(काष्ठा cn_msg *msg, काष्ठा netlink_skb_parms *nsp)
अणु
	काष्ठा uvesafb_task *utask;
	काष्ठा uvesafb_ktask *task;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस;

	अगर (msg->seq >= UVESAFB_TASKS_MAX)
		वापस;

	mutex_lock(&uvfb_lock);
	task = uvfb_tasks[msg->seq];

	अगर (!task || msg->ack != task->ack) अणु
		mutex_unlock(&uvfb_lock);
		वापस;
	पूर्ण

	utask = (काष्ठा uvesafb_task *)msg->data;

	/* Sanity checks क्रम the buffer length. */
	अगर (task->t.buf_len < utask->buf_len ||
	    utask->buf_len > msg->len - माप(*utask)) अणु
		mutex_unlock(&uvfb_lock);
		वापस;
	पूर्ण

	uvfb_tasks[msg->seq] = शून्य;
	mutex_unlock(&uvfb_lock);

	स_नकल(&task->t, utask, माप(*utask));

	अगर (task->t.buf_len && task->buf)
		स_नकल(task->buf, utask + 1, task->t.buf_len);

	complete(task->करोne);
	वापस;
पूर्ण

अटल पूर्णांक uvesafb_helper_start(व्योम)
अणु
	अक्षर *envp[] = अणु
		"HOME=/",
		"PATH=/sbin:/bin",
		शून्य,
	पूर्ण;

	अक्षर *argv[] = अणु
		v86d_path,
		शून्य,
	पूर्ण;

	वापस call_usermodehelper(v86d_path, argv, envp, UMH_WAIT_PROC);
पूर्ण

/*
 * Execute a uvesafb task.
 *
 * Returns 0 अगर the task is executed successfully.
 *
 * A message sent to the userspace consists of the uvesafb_task
 * काष्ठा and (optionally) a buffer. The uvesafb_task काष्ठा is
 * a simplअगरied version of uvesafb_ktask (its kernel counterpart)
 * containing only the रेजिस्टर values, flags and the length of
 * the buffer.
 *
 * Each message is asचिन्हित a sequence number (increased linearly)
 * and a अक्रमom ack number. The sequence number is used as a key
 * क्रम the uvfb_tasks array which holds poपूर्णांकers to uvesafb_ktask
 * काष्ठाs क्रम all requests.
 */
अटल पूर्णांक uvesafb_exec(काष्ठा uvesafb_ktask *task)
अणु
	अटल पूर्णांक seq;
	काष्ठा cn_msg *m;
	पूर्णांक err;
	पूर्णांक len = माप(task->t) + task->t.buf_len;

	/*
	 * Check whether the message isn't दीर्घer than the maximum
	 * allowed by connector.
	 */
	अगर (माप(*m) + len > CONNECTOR_MAX_MSG_SIZE) अणु
		pr_warn("message too long (%d), can't execute task\n",
			(पूर्णांक)(माप(*m) + len));
		वापस -E2BIG;
	पूर्ण

	m = kzalloc(माप(*m) + len, GFP_KERNEL);
	अगर (!m)
		वापस -ENOMEM;

	init_completion(task->करोne);

	स_नकल(&m->id, &uvesafb_cn_id, माप(m->id));
	m->seq = seq;
	m->len = len;
	m->ack = pअक्रमom_u32();

	/* uvesafb_task काष्ठाure */
	स_नकल(m + 1, &task->t, माप(task->t));

	/* Buffer */
	स_नकल((u8 *)(m + 1) + माप(task->t), task->buf, task->t.buf_len);

	/*
	 * Save the message ack number so that we can find the kernel
	 * part of this task when a reply is received from userspace.
	 */
	task->ack = m->ack;

	mutex_lock(&uvfb_lock);

	/* If all slots are taken -- bail out. */
	अगर (uvfb_tasks[seq]) अणु
		mutex_unlock(&uvfb_lock);
		err = -EBUSY;
		जाओ out;
	पूर्ण

	/* Save a poपूर्णांकer to the kernel part of the task काष्ठा. */
	uvfb_tasks[seq] = task;
	mutex_unlock(&uvfb_lock);

	err = cn_netlink_send(m, 0, 0, GFP_KERNEL);
	अगर (err == -ESRCH) अणु
		/*
		 * Try to start the userspace helper अगर sending
		 * the request failed the first समय.
		 */
		err = uvesafb_helper_start();
		अगर (err) अणु
			pr_err("failed to execute %s\n", v86d_path);
			pr_err("make sure that the v86d helper is installed and executable\n");
		पूर्ण अन्यथा अणु
			v86d_started = 1;
			err = cn_netlink_send(m, 0, 0, gfp_any());
			अगर (err == -ENOBUFS)
				err = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (err == -ENOBUFS)
		err = 0;

	अगर (!err && !(task->t.flags & TF_EXIT))
		err = !रुको_क्रम_completion_समयout(task->करोne,
				msecs_to_jअगरfies(UVESAFB_TIMEOUT));

	mutex_lock(&uvfb_lock);
	uvfb_tasks[seq] = शून्य;
	mutex_unlock(&uvfb_lock);

	seq++;
	अगर (seq >= UVESAFB_TASKS_MAX)
		seq = 0;
out:
	kमुक्त(m);
	वापस err;
पूर्ण

/*
 * Free a uvesafb_ktask काष्ठा.
 */
अटल व्योम uvesafb_मुक्त(काष्ठा uvesafb_ktask *task)
अणु
	अगर (task) अणु
		kमुक्त(task->करोne);
		kमुक्त(task);
	पूर्ण
पूर्ण

/*
 * Prepare a uvesafb_ktask काष्ठा to be used again.
 */
अटल व्योम uvesafb_reset(काष्ठा uvesafb_ktask *task)
अणु
	काष्ठा completion *cpl = task->करोne;

	स_रखो(task, 0, माप(*task));
	task->करोne = cpl;
पूर्ण

/*
 * Allocate and prepare a uvesafb_ktask काष्ठा.
 */
अटल काष्ठा uvesafb_ktask *uvesafb_prep(व्योम)
अणु
	काष्ठा uvesafb_ktask *task;

	task = kzalloc(माप(*task), GFP_KERNEL);
	अगर (task) अणु
		task->करोne = kzalloc(माप(*task->करोne), GFP_KERNEL);
		अगर (!task->करोne) अणु
			kमुक्त(task);
			task = शून्य;
		पूर्ण
	पूर्ण
	वापस task;
पूर्ण

अटल व्योम uvesafb_setup_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info, काष्ठा vbe_mode_ib *mode)
अणु
	काष्ठा uvesafb_par *par = info->par;

	var->vmode = FB_VMODE_NONINTERLACED;
	var->sync = FB_SYNC_VERT_HIGH_ACT;

	var->xres = mode->x_res;
	var->yres = mode->y_res;
	var->xres_भव = mode->x_res;
	var->yres_भव = (par->ypan) ?
			info->fix.smem_len / mode->bytes_per_scan_line :
			mode->y_res;
	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = mode->bits_per_pixel;

	अगर (var->bits_per_pixel == 15)
		var->bits_per_pixel = 16;

	अगर (var->bits_per_pixel > 8) अणु
		var->red.offset    = mode->red_off;
		var->red.length    = mode->red_len;
		var->green.offset  = mode->green_off;
		var->green.length  = mode->green_len;
		var->blue.offset   = mode->blue_off;
		var->blue.length   = mode->blue_len;
		var->transp.offset = mode->rsvd_off;
		var->transp.length = mode->rsvd_len;
	पूर्ण अन्यथा अणु
		var->red.offset    = 0;
		var->green.offset  = 0;
		var->blue.offset   = 0;
		var->transp.offset = 0;

		var->red.length    = 8;
		var->green.length  = 8;
		var->blue.length   = 8;
		var->transp.length = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक uvesafb_vbe_find_mode(काष्ठा uvesafb_par *par,
		पूर्णांक xres, पूर्णांक yres, पूर्णांक depth, अचिन्हित अक्षर flags)
अणु
	पूर्णांक i, match = -1, h = 0, d = 0x7fffffff;

	क्रम (i = 0; i < par->vbe_modes_cnt; i++) अणु
		h = असल(par->vbe_modes[i].x_res - xres) +
		    असल(par->vbe_modes[i].y_res - yres) +
		    असल(depth - par->vbe_modes[i].depth);

		/*
		 * We have an exact match in terms of resolution
		 * and depth.
		 */
		अगर (h == 0)
			वापस i;

		अगर (h < d || (h == d && par->vbe_modes[i].depth > depth)) अणु
			d = h;
			match = i;
		पूर्ण
	पूर्ण
	i = 1;

	अगर (flags & UVESAFB_EXACT_DEPTH &&
			par->vbe_modes[match].depth != depth)
		i = 0;

	अगर (flags & UVESAFB_EXACT_RES && d > 24)
		i = 0;

	अगर (i != 0)
		वापस match;
	अन्यथा
		वापस -1;
पूर्ण

अटल u8 *uvesafb_vbe_state_save(काष्ठा uvesafb_par *par)
अणु
	काष्ठा uvesafb_ktask *task;
	u8 *state;
	पूर्णांक err;

	अगर (!par->vbe_state_size)
		वापस शून्य;

	state = kदो_स्मृति(par->vbe_state_size, GFP_KERNEL);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	task = uvesafb_prep();
	अगर (!task) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0001;
	task->t.flags = TF_BUF_RET | TF_BUF_ESBX;
	task->t.buf_len = par->vbe_state_size;
	task->buf = state;
	err = uvesafb_exec(task);

	अगर (err || (task->t.regs.eax & 0xffff) != 0x004f) अणु
		pr_warn("VBE get state call failed (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);
		kमुक्त(state);
		state = शून्य;
	पूर्ण

	uvesafb_मुक्त(task);
	वापस state;
पूर्ण

अटल व्योम uvesafb_vbe_state_restore(काष्ठा uvesafb_par *par, u8 *state_buf)
अणु
	काष्ठा uvesafb_ktask *task;
	पूर्णांक err;

	अगर (!state_buf)
		वापस;

	task = uvesafb_prep();
	अगर (!task)
		वापस;

	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0002;
	task->t.buf_len = par->vbe_state_size;
	task->t.flags = TF_BUF_ESBX;
	task->buf = state_buf;

	err = uvesafb_exec(task);
	अगर (err || (task->t.regs.eax & 0xffff) != 0x004f)
		pr_warn("VBE state restore call failed (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);

	uvesafb_मुक्त(task);
पूर्ण

अटल पूर्णांक uvesafb_vbe_getinfo(काष्ठा uvesafb_ktask *task,
			       काष्ठा uvesafb_par *par)
अणु
	पूर्णांक err;

	task->t.regs.eax = 0x4f00;
	task->t.flags = TF_VBEIB;
	task->t.buf_len = माप(काष्ठा vbe_ib);
	task->buf = &par->vbe_ib;
	स_नकल(par->vbe_ib.vbe_signature, "VBE2", 4);

	err = uvesafb_exec(task);
	अगर (err || (task->t.regs.eax & 0xffff) != 0x004f) अणु
		pr_err("Getting VBE info block failed (eax=0x%x, err=%d)\n",
		       (u32)task->t.regs.eax, err);
		वापस -EINVAL;
	पूर्ण

	अगर (par->vbe_ib.vbe_version < 0x0200) अणु
		pr_err("Sorry, pre-VBE 2.0 cards are not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!par->vbe_ib.mode_list_ptr) अणु
		pr_err("Missing mode list!\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("");

	/*
	 * Convert string poपूर्णांकers and the mode list poपूर्णांकer पूर्णांकo
	 * usable addresses. Prपूर्णांक inक्रमmational messages about the
	 * video adapter and its venकरोr.
	 */
	अगर (par->vbe_ib.oem_venकरोr_name_ptr)
		pr_cont("%s, ",
			((अक्षर *)task->buf) + par->vbe_ib.oem_venकरोr_name_ptr);

	अगर (par->vbe_ib.oem_product_name_ptr)
		pr_cont("%s, ",
			((अक्षर *)task->buf) + par->vbe_ib.oem_product_name_ptr);

	अगर (par->vbe_ib.oem_product_rev_ptr)
		pr_cont("%s, ",
			((अक्षर *)task->buf) + par->vbe_ib.oem_product_rev_ptr);

	अगर (par->vbe_ib.oem_string_ptr)
		pr_cont("OEM: %s, ",
			((अक्षर *)task->buf) + par->vbe_ib.oem_string_ptr);

	pr_cont("VBE v%d.%d\n",
		(par->vbe_ib.vbe_version & 0xff00) >> 8,
		par->vbe_ib.vbe_version & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक uvesafb_vbe_geपंचांगodes(काष्ठा uvesafb_ktask *task,
				काष्ठा uvesafb_par *par)
अणु
	पूर्णांक off = 0, err;
	u16 *mode;

	par->vbe_modes_cnt = 0;

	/* Count available modes. */
	mode = (u16 *) (((u8 *)&par->vbe_ib) + par->vbe_ib.mode_list_ptr);
	जबतक (*mode != 0xffff) अणु
		par->vbe_modes_cnt++;
		mode++;
	पूर्ण

	par->vbe_modes = kसुस्मृति(par->vbe_modes_cnt,
				 माप(काष्ठा vbe_mode_ib),
				 GFP_KERNEL);
	अगर (!par->vbe_modes)
		वापस -ENOMEM;

	/* Get info about all available modes. */
	mode = (u16 *) (((u8 *)&par->vbe_ib) + par->vbe_ib.mode_list_ptr);
	जबतक (*mode != 0xffff) अणु
		काष्ठा vbe_mode_ib *mib;

		uvesafb_reset(task);
		task->t.regs.eax = 0x4f01;
		task->t.regs.ecx = (u32) *mode;
		task->t.flags = TF_BUF_RET | TF_BUF_ESDI;
		task->t.buf_len = माप(काष्ठा vbe_mode_ib);
		task->buf = par->vbe_modes + off;

		err = uvesafb_exec(task);
		अगर (err || (task->t.regs.eax & 0xffff) != 0x004f) अणु
			pr_warn("Getting mode info block for mode 0x%x failed (eax=0x%x, err=%d)\n",
				*mode, (u32)task->t.regs.eax, err);
			mode++;
			par->vbe_modes_cnt--;
			जारी;
		पूर्ण

		mib = task->buf;
		mib->mode_id = *mode;

		/*
		 * We only want modes that are supported with the current
		 * hardware configuration, color, graphics and that have
		 * support क्रम the LFB.
		 */
		अगर ((mib->mode_attr & VBE_MODE_MASK) == VBE_MODE_MASK &&
				 mib->bits_per_pixel >= 8)
			off++;
		अन्यथा
			par->vbe_modes_cnt--;

		mode++;
		mib->depth = mib->red_len + mib->green_len + mib->blue_len;

		/*
		 * Handle 8bpp modes and modes with broken color component
		 * lengths.
		 */
		अगर (mib->depth == 0 || (mib->depth == 24 &&
					mib->bits_per_pixel == 32))
			mib->depth = mib->bits_per_pixel;
	पूर्ण

	अगर (par->vbe_modes_cnt > 0)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

/*
 * The Protected Mode Interface is 32-bit x86 code, so we only run it on
 * x86 and not x86_64.
 */
#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक uvesafb_vbe_getpmi(काष्ठा uvesafb_ktask *task,
			      काष्ठा uvesafb_par *par)
अणु
	पूर्णांक i, err;

	uvesafb_reset(task);
	task->t.regs.eax = 0x4f0a;
	task->t.regs.ebx = 0x0;
	err = uvesafb_exec(task);
	अगर (err)
		वापस err;

	अगर ((task->t.regs.eax & 0xffff) != 0x4f || task->t.regs.es < 0xc000) अणु
		par->pmi_setpal = par->ypan = 0;
	पूर्ण अन्यथा अणु
		par->pmi_base = (u16 *)phys_to_virt(((u32)task->t.regs.es << 4)
						+ task->t.regs.edi);
		par->pmi_start = (u8 *)par->pmi_base + par->pmi_base[1];
		par->pmi_pal = (u8 *)par->pmi_base + par->pmi_base[2];
		pr_info("protected mode interface info at %04x:%04x\n",
			(u16)task->t.regs.es, (u16)task->t.regs.edi);
		pr_info("pmi: set display start = %p, set palette = %p\n",
			par->pmi_start, par->pmi_pal);

		अगर (par->pmi_base[3]) अणु
			pr_info("pmi: ports =");
			क्रम (i = par->pmi_base[3]/2;
					par->pmi_base[i] != 0xffff; i++)
				pr_cont(" %x", par->pmi_base[i]);
			pr_cont("\n");

			अगर (par->pmi_base[i] != 0xffff) अणु
				pr_info("can't handle memory requests, pmi disabled\n");
				par->ypan = par->pmi_setpal = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

/*
 * Check whether a video mode is supported by the Video BIOS and is
 * compatible with the monitor limits.
 */
अटल पूर्णांक uvesafb_is_valid_mode(काष्ठा fb_videomode *mode,
				 काष्ठा fb_info *info)
अणु
	अगर (info->monspecs.gtf) अणु
		fb_videomode_to_var(&info->var, mode);
		अगर (fb_validate_mode(&info->var, info))
			वापस 0;
	पूर्ण

	अगर (uvesafb_vbe_find_mode(info->par, mode->xres, mode->yres, 8,
				UVESAFB_EXACT_RES) == -1)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक uvesafb_vbe_getedid(काष्ठा uvesafb_ktask *task, काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक err = 0;

	अगर (noedid || par->vbe_ib.vbe_version < 0x0300)
		वापस -EINVAL;

	task->t.regs.eax = 0x4f15;
	task->t.regs.ebx = 0;
	task->t.regs.ecx = 0;
	task->t.buf_len = 0;
	task->t.flags = 0;

	err = uvesafb_exec(task);

	अगर ((task->t.regs.eax & 0xffff) != 0x004f || err)
		वापस -EINVAL;

	अगर ((task->t.regs.ebx & 0x3) == 3) अणु
		pr_info("VBIOS/hardware supports both DDC1 and DDC2 transfers\n");
	पूर्ण अन्यथा अगर ((task->t.regs.ebx & 0x3) == 2) अणु
		pr_info("VBIOS/hardware supports DDC2 transfers\n");
	पूर्ण अन्यथा अगर ((task->t.regs.ebx & 0x3) == 1) अणु
		pr_info("VBIOS/hardware supports DDC1 transfers\n");
	पूर्ण अन्यथा अणु
		pr_info("VBIOS/hardware doesn't support DDC transfers\n");
		वापस -EINVAL;
	पूर्ण

	task->t.regs.eax = 0x4f15;
	task->t.regs.ebx = 1;
	task->t.regs.ecx = task->t.regs.edx = 0;
	task->t.flags = TF_BUF_RET | TF_BUF_ESDI;
	task->t.buf_len = EDID_LENGTH;
	task->buf = kzalloc(EDID_LENGTH, GFP_KERNEL);
	अगर (!task->buf)
		वापस -ENOMEM;

	err = uvesafb_exec(task);

	अगर ((task->t.regs.eax & 0xffff) == 0x004f && !err) अणु
		fb_edid_to_monspecs(task->buf, &info->monspecs);

		अगर (info->monspecs.vfmax && info->monspecs.hfmax) अणु
			/*
			 * If the maximum pixel घड़ी wasn't specअगरied in
			 * the EDID block, set it to 300 MHz.
			 */
			अगर (info->monspecs.dclkmax == 0)
				info->monspecs.dclkmax = 300 * 1000000;
			info->monspecs.gtf = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	kमुक्त(task->buf);
	वापस err;
पूर्ण

अटल व्योम uvesafb_vbe_geपंचांगonspecs(काष्ठा uvesafb_ktask *task,
				    काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक i;

	स_रखो(&info->monspecs, 0, माप(info->monspecs));

	/*
	 * If we करोn't get all necessary data from the EDID block,
	 * mark it as incompatible with the GTF and set nocrtc so
	 * that we always use the शेष BIOS refresh rate.
	 */
	अगर (uvesafb_vbe_getedid(task, info)) अणु
		info->monspecs.gtf = 0;
		par->nocrtc = 1;
	पूर्ण

	/* Kernel command line overrides. */
	अगर (maxclk)
		info->monspecs.dclkmax = maxclk * 1000000;
	अगर (maxvf)
		info->monspecs.vfmax = maxvf;
	अगर (maxhf)
		info->monspecs.hfmax = maxhf * 1000;

	/*
	 * In हाल DDC transfers are not supported, the user can provide
	 * monitor limits manually. Lower limits are set to "safe" values.
	 */
	अगर (info->monspecs.gtf == 0 && maxclk && maxvf && maxhf) अणु
		info->monspecs.dclkmin = 0;
		info->monspecs.vfmin = 60;
		info->monspecs.hfmin = 29000;
		info->monspecs.gtf = 1;
		par->nocrtc = 0;
	पूर्ण

	अगर (info->monspecs.gtf)
		pr_info("monitor limits: vf = %d Hz, hf = %d kHz, clk = %d MHz\n",
			info->monspecs.vfmax,
			(पूर्णांक)(info->monspecs.hfmax / 1000),
			(पूर्णांक)(info->monspecs.dclkmax / 1000000));
	अन्यथा
		pr_info("no monitor limits have been set, default refresh rate will be used\n");

	/* Add VBE modes to the modelist. */
	क्रम (i = 0; i < par->vbe_modes_cnt; i++) अणु
		काष्ठा fb_var_screeninfo var;
		काष्ठा vbe_mode_ib *mode;
		काष्ठा fb_videomode vmode;

		mode = &par->vbe_modes[i];
		स_रखो(&var, 0, माप(var));

		var.xres = mode->x_res;
		var.yres = mode->y_res;

		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON, 60, &var, info);
		fb_var_to_videomode(&vmode, &var);
		fb_add_videomode(&vmode, &info->modelist);
	पूर्ण

	/* Add valid VESA modes to our modelist. */
	क्रम (i = 0; i < VESA_MODEDB_SIZE; i++) अणु
		अगर (uvesafb_is_valid_mode((काष्ठा fb_videomode *)
						&vesa_modes[i], info))
			fb_add_videomode(&vesa_modes[i], &info->modelist);
	पूर्ण

	क्रम (i = 0; i < info->monspecs.modedb_len; i++) अणु
		अगर (uvesafb_is_valid_mode(&info->monspecs.modedb[i], info))
			fb_add_videomode(&info->monspecs.modedb[i],
					&info->modelist);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम uvesafb_vbe_माला_लोtatesize(काष्ठा uvesafb_ktask *task,
				     काष्ठा uvesafb_par *par)
अणु
	पूर्णांक err;

	uvesafb_reset(task);

	/*
	 * Get the VBE state buffer size. We want all available
	 * hardware state data (CL = 0x0f).
	 */
	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0000;
	task->t.flags = 0;

	err = uvesafb_exec(task);

	अगर (err || (task->t.regs.eax & 0xffff) != 0x004f) अणु
		pr_warn("VBE state buffer size cannot be determined (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);
		par->vbe_state_size = 0;
		वापस;
	पूर्ण

	par->vbe_state_size = 64 * (task->t.regs.ebx & 0xffff);
पूर्ण

अटल पूर्णांक uvesafb_vbe_init(काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_ktask *task = शून्य;
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक err;

	task = uvesafb_prep();
	अगर (!task)
		वापस -ENOMEM;

	err = uvesafb_vbe_getinfo(task, par);
	अगर (err)
		जाओ out;

	err = uvesafb_vbe_geपंचांगodes(task, par);
	अगर (err)
		जाओ out;

	par->nocrtc = nocrtc;
#अगर_घोषित CONFIG_X86_32
	par->pmi_setpal = pmi_setpal;
	par->ypan = ypan;

	अगर (par->pmi_setpal || par->ypan) अणु
		अगर (__supported_pte_mask & _PAGE_NX) अणु
			par->pmi_setpal = par->ypan = 0;
			pr_warn("NX protection is active, better not use the PMI\n");
		पूर्ण अन्यथा अणु
			uvesafb_vbe_getpmi(task, par);
		पूर्ण
	पूर्ण
#अन्यथा
	/* The रक्षित mode पूर्णांकerface is not available on non-x86. */
	par->pmi_setpal = par->ypan = 0;
#पूर्ण_अगर

	INIT_LIST_HEAD(&info->modelist);
	uvesafb_vbe_geपंचांगonspecs(task, info);
	uvesafb_vbe_माला_लोtatesize(task, par);

out:	uvesafb_मुक्त(task);
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_vbe_init_mode(काष्ठा fb_info *info)
अणु
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *mode;
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक i, modeid;

	/* Has the user requested a specअगरic VESA mode? */
	अगर (vbemode) अणु
		क्रम (i = 0; i < par->vbe_modes_cnt; i++) अणु
			अगर (par->vbe_modes[i].mode_id == vbemode) अणु
				modeid = i;
				uvesafb_setup_var(&info->var, info,
						&par->vbe_modes[modeid]);
				fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON, 60,
						&info->var, info);
				/*
				 * With pixघड़ी set to 0, the शेष BIOS
				 * timings will be used in set_par().
				 */
				info->var.pixघड़ी = 0;
				जाओ goपंचांगode;
			पूर्ण
		पूर्ण
		pr_info("requested VBE mode 0x%x is unavailable\n", vbemode);
		vbemode = 0;
	पूर्ण

	/* Count the modes in the modelist */
	i = 0;
	list_क्रम_each(pos, &info->modelist)
		i++;

	/*
	 * Convert the modelist पूर्णांकo a modedb so that we can use it with
	 * fb_find_mode().
	 */
	mode = kसुस्मृति(i, माप(*mode), GFP_KERNEL);
	अगर (mode) अणु
		i = 0;
		list_क्रम_each(pos, &info->modelist) अणु
			modelist = list_entry(pos, काष्ठा fb_modelist, list);
			mode[i] = modelist->mode;
			i++;
		पूर्ण

		अगर (!mode_option)
			mode_option = UVESAFB_DEFAULT_MODE;

		i = fb_find_mode(&info->var, info, mode_option, mode, i,
			शून्य, 8);

		kमुक्त(mode);
	पूर्ण

	/* fb_find_mode() failed */
	अगर (i == 0) अणु
		info->var.xres = 640;
		info->var.yres = 480;
		mode = (काष्ठा fb_videomode *)
				fb_find_best_mode(&info->var, &info->modelist);

		अगर (mode) अणु
			fb_videomode_to_var(&info->var, mode);
		पूर्ण अन्यथा अणु
			modeid = par->vbe_modes[0].mode_id;
			uvesafb_setup_var(&info->var, info,
					&par->vbe_modes[modeid]);
			fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON, 60,
					&info->var, info);

			जाओ goपंचांगode;
		पूर्ण
	पूर्ण

	/* Look क्रम a matching VBE mode. */
	modeid = uvesafb_vbe_find_mode(par, info->var.xres, info->var.yres,
			info->var.bits_per_pixel, UVESAFB_EXACT_RES);

	अगर (modeid == -1)
		वापस -EINVAL;

	uvesafb_setup_var(&info->var, info, &par->vbe_modes[modeid]);

goपंचांगode:
	/*
	 * If we are not VBE3.0+ compliant, we're करोne -- the BIOS will
	 * ignore our timings anyway.
	 */
	अगर (par->vbe_ib.vbe_version < 0x0300 || par->nocrtc)
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON, 60,
					&info->var, info);

	वापस modeid;
पूर्ण

अटल पूर्णांक uvesafb_setpalette(काष्ठा uvesafb_pal_entry *entries, पूर्णांक count,
		पूर्णांक start, काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_ktask *task;
#अगर_घोषित CONFIG_X86
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक i = par->mode_idx;
#पूर्ण_अगर
	पूर्णांक err = 0;

	/*
	 * We support palette modअगरications क्रम 8 bpp modes only, so
	 * there can never be more than 256 entries.
	 */
	अगर (start + count > 256)
		वापस -EINVAL;

#अगर_घोषित CONFIG_X86
	/* Use VGA रेजिस्टरs अगर mode is VGA-compatible. */
	अगर (i >= 0 && i < par->vbe_modes_cnt &&
	    par->vbe_modes[i].mode_attr & VBE_MODE_VGACOMPAT) अणु
		क्रम (i = 0; i < count; i++) अणु
			outb_p(start + i,        dac_reg);
			outb_p(entries[i].red,   dac_val);
			outb_p(entries[i].green, dac_val);
			outb_p(entries[i].blue,  dac_val);
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_X86_32
	अन्यथा अगर (par->pmi_setpal) अणु
		__यंत्र__ __अस्थिर__(
		"call *(%%esi)"
		: /* no वापस value */
		: "a" (0x4f09),         /* EAX */
		  "b" (0),              /* EBX */
		  "c" (count),          /* ECX */
		  "d" (start),          /* EDX */
		  "D" (entries),        /* EDI */
		  "S" (&par->pmi_pal)); /* ESI */
	पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */
	अन्यथा
#पूर्ण_अगर /* CONFIG_X86 */
	अणु
		task = uvesafb_prep();
		अगर (!task)
			वापस -ENOMEM;

		task->t.regs.eax = 0x4f09;
		task->t.regs.ebx = 0x0;
		task->t.regs.ecx = count;
		task->t.regs.edx = start;
		task->t.flags = TF_BUF_ESDI;
		task->t.buf_len = माप(काष्ठा uvesafb_pal_entry) * count;
		task->buf = entries;

		err = uvesafb_exec(task);
		अगर ((task->t.regs.eax & 0xffff) != 0x004f)
			err = 1;

		uvesafb_मुक्त(task);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
		अचिन्हित blue, अचिन्हित transp,
		काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_pal_entry entry;
	पूर्णांक shअगरt = 16 - dac_width;
	पूर्णांक err = 0;

	अगर (regno >= info->cmap.len)
		वापस -EINVAL;

	अगर (info->var.bits_per_pixel == 8) अणु
		entry.red   = red   >> shअगरt;
		entry.green = green >> shअगरt;
		entry.blue  = blue  >> shअगरt;
		entry.pad   = 0;

		err = uvesafb_setpalette(&entry, 1, regno, info);
	पूर्ण अन्यथा अगर (regno < 16) अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 16:
			अगर (info->var.red.offset == 10) अणु
				/* 1:5:5:5 */
				((u32 *) (info->pseuकरो_palette))[regno] =
						((red   & 0xf800) >>  1) |
						((green & 0xf800) >>  6) |
						((blue  & 0xf800) >> 11);
			पूर्ण अन्यथा अणु
				/* 0:5:6:5 */
				((u32 *) (info->pseuकरो_palette))[regno] =
						((red   & 0xf800)      ) |
						((green & 0xfc00) >>  5) |
						((blue  & 0xf800) >> 11);
			पूर्ण
			अवरोध;

		हाल 24:
		हाल 32:
			red   >>= 8;
			green >>= 8;
			blue  >>= 8;
			((u32 *)(info->pseuकरो_palette))[regno] =
				(red   << info->var.red.offset)   |
				(green << info->var.green.offset) |
				(blue  << info->var.blue.offset);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_pal_entry *entries;
	पूर्णांक shअगरt = 16 - dac_width;
	पूर्णांक i, err = 0;

	अगर (info->var.bits_per_pixel == 8) अणु
		अगर (cmap->start + cmap->len > info->cmap.start +
		    info->cmap.len || cmap->start < info->cmap.start)
			वापस -EINVAL;

		entries = kदो_स्मृति_array(cmap->len, माप(*entries),
					GFP_KERNEL);
		अगर (!entries)
			वापस -ENOMEM;

		क्रम (i = 0; i < cmap->len; i++) अणु
			entries[i].red   = cmap->red[i]   >> shअगरt;
			entries[i].green = cmap->green[i] >> shअगरt;
			entries[i].blue  = cmap->blue[i]  >> shअगरt;
			entries[i].pad   = 0;
		पूर्ण
		err = uvesafb_setpalette(entries, cmap->len, cmap->start, info);
		kमुक्त(entries);
	पूर्ण अन्यथा अणु
		/*
		 * For modes with bpp > 8, we only set the pseuकरो palette in
		 * the fb_info काष्ठा. We rely on uvesafb_setcolreg to करो all
		 * sanity checking.
		 */
		क्रम (i = 0; i < cmap->len; i++) अणु
			err |= uvesafb_setcolreg(cmap->start + i, cmap->red[i],
						cmap->green[i], cmap->blue[i],
						0, info);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_pan_display(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
#अगर_घोषित CONFIG_X86_32
	पूर्णांक offset;
	काष्ठा uvesafb_par *par = info->par;

	offset = (var->yoffset * info->fix.line_length + var->xoffset) / 4;

	/*
	 * It turns out it's not the best idea to करो panning via vm86,
	 * so we only allow it अगर we have a PMI.
	 */
	अगर (par->pmi_start) अणु
		__यंत्र__ __अस्थिर__(
			"call *(%%edi)"
			: /* no वापस value */
			: "a" (0x4f07),         /* EAX */
			  "b" (0),              /* EBX */
			  "c" (offset),         /* ECX */
			  "d" (offset >> 16),   /* EDX */
			  "D" (&par->pmi_start));    /* EDI */
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक uvesafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_ktask *task;
	पूर्णांक err = 1;
#अगर_घोषित CONFIG_X86
	काष्ठा uvesafb_par *par = info->par;

	अगर (par->vbe_ib.capabilities & VBE_CAP_VGACOMPAT) अणु
		पूर्णांक loop = 10000;
		u8 seq = 0, crtc17 = 0;

		अगर (blank == FB_BLANK_POWERDOWN) अणु
			seq = 0x20;
			crtc17 = 0x00;
			err = 0;
		पूर्ण अन्यथा अणु
			seq = 0x00;
			crtc17 = 0x80;
			err = (blank == FB_BLANK_UNBLANK) ? 0 : -EINVAL;
		पूर्ण

		vga_wseq(शून्य, 0x00, 0x01);
		seq |= vga_rseq(शून्य, 0x01) & ~0x20;
		vga_wseq(शून्य, 0x00, seq);

		crtc17 |= vga_rcrt(शून्य, 0x17) & ~0x80;
		जबतक (loop--);
		vga_wcrt(शून्य, 0x17, crtc17);
		vga_wseq(शून्य, 0x00, 0x03);
	पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_X86 */
	अणु
		task = uvesafb_prep();
		अगर (!task)
			वापस -ENOMEM;

		task->t.regs.eax = 0x4f10;
		चयन (blank) अणु
		हाल FB_BLANK_UNBLANK:
			task->t.regs.ebx = 0x0001;
			अवरोध;
		हाल FB_BLANK_NORMAL:
			task->t.regs.ebx = 0x0101;	/* standby */
			अवरोध;
		हाल FB_BLANK_POWERDOWN:
			task->t.regs.ebx = 0x0401;	/* घातerकरोwn */
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण

		err = uvesafb_exec(task);
		अगर (err || (task->t.regs.eax & 0xffff) != 0x004f)
			err = 1;
out:		uvesafb_मुक्त(task);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक cnt = atomic_पढ़ो(&par->ref_count);
	u8 *buf = शून्य;

	अगर (!cnt && par->vbe_state_size) अणु
		buf =  uvesafb_vbe_state_save(par);
		अगर (IS_ERR(buf)) अणु
			pr_warn("save hardware state failed, error code is %ld!\n",
				PTR_ERR(buf));
		पूर्ण अन्यथा अणु
			par->vbe_state_orig = buf;
		पूर्ण
	पूर्ण

	atomic_inc(&par->ref_count);
	वापस 0;
पूर्ण

अटल पूर्णांक uvesafb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा uvesafb_ktask *task = शून्य;
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक cnt = atomic_पढ़ो(&par->ref_count);

	अगर (!cnt)
		वापस -EINVAL;

	अगर (cnt != 1)
		जाओ out;

	task = uvesafb_prep();
	अगर (!task)
		जाओ out;

	/* First, try to set the standard 80x25 text mode. */
	task->t.regs.eax = 0x0003;
	uvesafb_exec(task);

	/*
	 * Now try to restore whatever hardware state we might have
	 * saved when the fb device was first खोलोed.
	 */
	uvesafb_vbe_state_restore(par, par->vbe_state_orig);
out:
	atomic_dec(&par->ref_count);
	uvesafb_मुक्त(task);
	वापस 0;
पूर्ण

अटल पूर्णांक uvesafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_par *par = info->par;
	काष्ठा uvesafb_ktask *task = शून्य;
	काष्ठा vbe_crtc_ib *crtc = शून्य;
	काष्ठा vbe_mode_ib *mode = शून्य;
	पूर्णांक i, err = 0, depth = info->var.bits_per_pixel;

	अगर (depth > 8 && depth != 32)
		depth = info->var.red.length + info->var.green.length +
			info->var.blue.length;

	i = uvesafb_vbe_find_mode(par, info->var.xres, info->var.yres, depth,
				 UVESAFB_EXACT_RES | UVESAFB_EXACT_DEPTH);
	अगर (i >= 0)
		mode = &par->vbe_modes[i];
	अन्यथा
		वापस -EINVAL;

	task = uvesafb_prep();
	अगर (!task)
		वापस -ENOMEM;
seपंचांगode:
	task->t.regs.eax = 0x4f02;
	task->t.regs.ebx = mode->mode_id | 0x4000;	/* use LFB */

	अगर (par->vbe_ib.vbe_version >= 0x0300 && !par->nocrtc &&
	    info->var.pixघड़ी != 0) अणु
		task->t.regs.ebx |= 0x0800;		/* use CRTC data */
		task->t.flags = TF_BUF_ESDI;
		crtc = kzalloc(माप(काष्ठा vbe_crtc_ib), GFP_KERNEL);
		अगर (!crtc) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		crtc->horiz_start = info->var.xres + info->var.right_margin;
		crtc->horiz_end	  = crtc->horiz_start + info->var.hsync_len;
		crtc->horiz_total = crtc->horiz_end + info->var.left_margin;

		crtc->vert_start  = info->var.yres + info->var.lower_margin;
		crtc->vert_end    = crtc->vert_start + info->var.vsync_len;
		crtc->vert_total  = crtc->vert_end + info->var.upper_margin;

		crtc->pixel_घड़ी = PICOS2KHZ(info->var.pixघड़ी) * 1000;
		crtc->refresh_rate = (u16)(100 * (crtc->pixel_घड़ी /
				(crtc->vert_total * crtc->horiz_total)));

		अगर (info->var.vmode & FB_VMODE_DOUBLE)
			crtc->flags |= 0x1;
		अगर (info->var.vmode & FB_VMODE_INTERLACED)
			crtc->flags |= 0x2;
		अगर (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
			crtc->flags |= 0x4;
		अगर (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
			crtc->flags |= 0x8;
		स_नकल(&par->crtc, crtc, माप(*crtc));
	पूर्ण अन्यथा अणु
		स_रखो(&par->crtc, 0, माप(*crtc));
	पूर्ण

	task->t.buf_len = माप(काष्ठा vbe_crtc_ib);
	task->buf = &par->crtc;

	err = uvesafb_exec(task);
	अगर (err || (task->t.regs.eax & 0xffff) != 0x004f) अणु
		/*
		 * The mode चयन might have failed because we tried to
		 * use our own timings.  Try again with the शेष timings.
		 */
		अगर (crtc != शून्य) अणु
			pr_warn("mode switch failed (eax=0x%x, err=%d) - trying again with default timings\n",
				task->t.regs.eax, err);
			uvesafb_reset(task);
			kमुक्त(crtc);
			crtc = शून्य;
			info->var.pixघड़ी = 0;
			जाओ seपंचांगode;
		पूर्ण अन्यथा अणु
			pr_err("mode switch failed (eax=0x%x, err=%d)\n",
			       task->t.regs.eax, err);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
	par->mode_idx = i;

	/* For 8bpp modes, always try to set the DAC to 8 bits. */
	अगर (par->vbe_ib.capabilities & VBE_CAP_CAN_SWITCH_DAC &&
	    mode->bits_per_pixel <= 8) अणु
		uvesafb_reset(task);
		task->t.regs.eax = 0x4f08;
		task->t.regs.ebx = 0x0800;

		err = uvesafb_exec(task);
		अगर (err || (task->t.regs.eax & 0xffff) != 0x004f ||
		    ((task->t.regs.ebx & 0xff00) >> 8) != 8) अणु
			dac_width = 6;
		पूर्ण अन्यथा अणु
			dac_width = 8;
		पूर्ण
	पूर्ण

	info->fix.visual = (info->var.bits_per_pixel == 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = mode->bytes_per_scan_line;

out:
	kमुक्त(crtc);
	uvesafb_मुक्त(task);

	वापस err;
पूर्ण

अटल व्योम uvesafb_check_limits(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	स्थिर काष्ठा fb_videomode *mode;
	काष्ठा uvesafb_par *par = info->par;

	/*
	 * If pixघड़ी is set to 0, then we're using शेष BIOS timings
	 * and thus करोn't have to perक्रमm any checks here.
	 */
	अगर (!var->pixघड़ी)
		वापस;

	अगर (par->vbe_ib.vbe_version < 0x0300) अणु
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON, 60, var, info);
		वापस;
	पूर्ण

	अगर (!fb_validate_mode(var, info))
		वापस;

	mode = fb_find_best_mode(var, &info->modelist);
	अगर (mode) अणु
		अगर (mode->xres == var->xres && mode->yres == var->yres &&
		    !(mode->vmode & (FB_VMODE_INTERLACED | FB_VMODE_DOUBLE))) अणु
			fb_videomode_to_var(var, mode);
			वापस;
		पूर्ण
	पूर्ण

	अगर (info->monspecs.gtf && !fb_get_mode(FB_MAXTIMINGS, 0, var, info))
		वापस;
	/* Use शेष refresh rate */
	var->pixघड़ी = 0;
पूर्ण

अटल पूर्णांक uvesafb_check_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_par *par = info->par;
	काष्ठा vbe_mode_ib *mode = शून्य;
	पूर्णांक match = -1;
	पूर्णांक depth = var->red.length + var->green.length + var->blue.length;

	/*
	 * Various apps will use bits_per_pixel to set the color depth,
	 * which is theoretically incorrect, but which we'll try to handle
	 * here.
	 */
	अगर (depth == 0 || असल(depth - var->bits_per_pixel) >= 8)
		depth = var->bits_per_pixel;

	match = uvesafb_vbe_find_mode(par, var->xres, var->yres, depth,
						UVESAFB_EXACT_RES);
	अगर (match == -1)
		वापस -EINVAL;

	mode = &par->vbe_modes[match];
	uvesafb_setup_var(var, info, mode);

	/*
	 * Check whether we have remapped enough memory क्रम this mode.
	 * We might be called at an early stage, when we haven't remapped
	 * any memory yet, in which हाल we simply skip the check.
	 */
	अगर (var->yres * mode->bytes_per_scan_line > info->fix.smem_len
						&& info->fix.smem_len)
		वापस -EINVAL;

	अगर ((var->vmode & FB_VMODE_DOUBLE) &&
				!(par->vbe_modes[match].mode_attr & 0x100))
		var->vmode &= ~FB_VMODE_DOUBLE;

	अगर ((var->vmode & FB_VMODE_INTERLACED) &&
				!(par->vbe_modes[match].mode_attr & 0x200))
		var->vmode &= ~FB_VMODE_INTERLACED;

	uvesafb_check_limits(var, info);

	var->xres_भव = var->xres;
	var->yres_भव = (par->ypan) ?
				info->fix.smem_len / mode->bytes_per_scan_line :
				var->yres;
	वापस 0;
पूर्ण

अटल काष्ठा fb_ops uvesafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= uvesafb_खोलो,
	.fb_release	= uvesafb_release,
	.fb_setcolreg	= uvesafb_setcolreg,
	.fb_setcmap	= uvesafb_setcmap,
	.fb_pan_display	= uvesafb_pan_display,
	.fb_blank	= uvesafb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_check_var	= uvesafb_check_var,
	.fb_set_par	= uvesafb_set_par,
पूर्ण;

अटल व्योम uvesafb_init_info(काष्ठा fb_info *info, काष्ठा vbe_mode_ib *mode)
अणु
	अचिन्हित पूर्णांक size_vmode;
	अचिन्हित पूर्णांक size_remap;
	अचिन्हित पूर्णांक माप_प्रकारotal;
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक i, h;

	info->pseuकरो_palette = ((u8 *)info->par + माप(काष्ठा uvesafb_par));
	info->fix = uvesafb_fix;
	info->fix.ypanstep = par->ypan ? 1 : 0;
	info->fix.ywrapstep = (par->ypan > 1) ? 1 : 0;

	/* Disable blanking अगर the user requested so. */
	अगर (!blank)
		uvesafb_ops.fb_blank = शून्य;

	/*
	 * Find out how much IO memory is required क्रम the mode with
	 * the highest resolution.
	 */
	size_remap = 0;
	क्रम (i = 0; i < par->vbe_modes_cnt; i++) अणु
		h = par->vbe_modes[i].bytes_per_scan_line *
					par->vbe_modes[i].y_res;
		अगर (h > size_remap)
			size_remap = h;
	पूर्ण
	size_remap *= 2;

	/*
	 *   size_vmode -- that is the amount of memory needed क्रम the
	 *                 used video mode, i.e. the minimum amount of
	 *                 memory we need.
	 */
	size_vmode = info->var.yres * mode->bytes_per_scan_line;

	/*
	 *   माप_प्रकारotal -- all video memory we have. Used क्रम mtrr
	 *                 entries, resource allocation and bounds
	 *                 checking.
	 */
	माप_प्रकारotal = par->vbe_ib.total_memory * 65536;
	अगर (vram_total)
		माप_प्रकारotal = vram_total * 1024 * 1024;
	अगर (माप_प्रकारotal < size_vmode)
		माप_प्रकारotal = size_vmode;

	/*
	 *   size_remap -- the amount of video memory we are going to
	 *                 use क्रम vesafb.  With modern cards it is no
	 *                 option to simply use माप_प्रकारotal as th
	 *                 wastes plenty of kernel address space.
	 */
	अगर (vram_remap)
		size_remap = vram_remap * 1024 * 1024;
	अगर (size_remap < size_vmode)
		size_remap = size_vmode;
	अगर (size_remap > माप_प्रकारotal)
		size_remap = माप_प्रकारotal;

	info->fix.smem_len = size_remap;
	info->fix.smem_start = mode->phys_base_ptr;

	/*
	 * We have to set yres_भव here because when setup_var() was
	 * called, smem_len wasn't defined yet.
	 */
	info->var.yres_भव = info->fix.smem_len /
				 mode->bytes_per_scan_line;

	अगर (par->ypan && info->var.yres_भव > info->var.yres) अणु
		pr_info("scrolling: %s using protected mode interface, yres_virtual=%d\n",
			(par->ypan > 1) ? "ywrap" : "ypan",
			info->var.yres_भव);
	पूर्ण अन्यथा अणु
		pr_info("scrolling: redraw\n");
		info->var.yres_भव = info->var.yres;
		par->ypan = 0;
	पूर्ण

	info->flags = FBINFO_FLAG_DEFAULT |
			(par->ypan ? FBINFO_HWACCEL_YPAN : 0);

	अगर (!par->ypan)
		uvesafb_ops.fb_pan_display = शून्य;
पूर्ण

अटल व्योम uvesafb_init_mtrr(काष्ठा fb_info *info)
अणु
	काष्ठा uvesafb_par *par = info->par;

	अगर (mtrr && !(info->fix.smem_start & (PAGE_SIZE - 1))) अणु
		पूर्णांक temp_size = info->fix.smem_len;

		पूर्णांक rc;

		/* Find the largest घातer-of-two */
		temp_size = roundup_घात_of_two(temp_size);

		/* Try and find a घातer of two to add */
		करो अणु
			rc = arch_phys_wc_add(info->fix.smem_start, temp_size);
			temp_size >>= 1;
		पूर्ण जबतक (temp_size >= PAGE_SIZE && rc == -EINVAL);

		अगर (rc >= 0)
			par->mtrr_handle = rc;
	पूर्ण
पूर्ण

अटल व्योम uvesafb_ioremap(काष्ठा fb_info *info)
अणु
	info->screen_base = ioremap_wc(info->fix.smem_start, info->fix.smem_len);
पूर्ण

अटल sमाप_प्रकार uvesafb_show_vbe_ver(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	वापस snम_लिखो(buf, PAGE_SIZE, "%.4x\n", par->vbe_ib.vbe_version);
पूर्ण

अटल DEVICE_ATTR(vbe_version, S_IRUGO, uvesafb_show_vbe_ver, शून्य);

अटल sमाप_प्रकार uvesafb_show_vbe_modes(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < par->vbe_modes_cnt && ret < PAGE_SIZE; i++) अणु
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
			"%dx%d-%d, 0x%.4x\n",
			par->vbe_modes[i].x_res, par->vbe_modes[i].y_res,
			par->vbe_modes[i].depth, par->vbe_modes[i].mode_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(vbe_modes, S_IRUGO, uvesafb_show_vbe_modes, शून्य);

अटल sमाप_प्रकार uvesafb_show_venकरोr(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	अगर (par->vbe_ib.oem_venकरोr_name_ptr)
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", (अक्षर *)
			(&par->vbe_ib) + par->vbe_ib.oem_venकरोr_name_ptr);
	अन्यथा
		वापस 0;
पूर्ण

अटल DEVICE_ATTR(oem_venकरोr, S_IRUGO, uvesafb_show_venकरोr, शून्य);

अटल sमाप_प्रकार uvesafb_show_product_name(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	अगर (par->vbe_ib.oem_product_name_ptr)
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", (अक्षर *)
			(&par->vbe_ib) + par->vbe_ib.oem_product_name_ptr);
	अन्यथा
		वापस 0;
पूर्ण

अटल DEVICE_ATTR(oem_product_name, S_IRUGO, uvesafb_show_product_name, शून्य);

अटल sमाप_प्रकार uvesafb_show_product_rev(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	अगर (par->vbe_ib.oem_product_rev_ptr)
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", (अक्षर *)
			(&par->vbe_ib) + par->vbe_ib.oem_product_rev_ptr);
	अन्यथा
		वापस 0;
पूर्ण

अटल DEVICE_ATTR(oem_product_rev, S_IRUGO, uvesafb_show_product_rev, शून्य);

अटल sमाप_प्रकार uvesafb_show_oem_string(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	अगर (par->vbe_ib.oem_string_ptr)
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			(अक्षर *)(&par->vbe_ib) + par->vbe_ib.oem_string_ptr);
	अन्यथा
		वापस 0;
पूर्ण

अटल DEVICE_ATTR(oem_string, S_IRUGO, uvesafb_show_oem_string, शून्य);

अटल sमाप_प्रकार uvesafb_show_nocrtc(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", par->nocrtc);
पूर्ण

अटल sमाप_प्रकार uvesafb_store_nocrtc(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा uvesafb_par *par = info->par;

	अगर (count > 0) अणु
		अगर (buf[0] == '0')
			par->nocrtc = 0;
		अन्यथा
			par->nocrtc = 1;
	पूर्ण
	वापस count;
पूर्ण

अटल DEVICE_ATTR(nocrtc, S_IRUGO | S_IWUSR, uvesafb_show_nocrtc,
			uvesafb_store_nocrtc);

अटल काष्ठा attribute *uvesafb_dev_attrs[] = अणु
	&dev_attr_vbe_version.attr,
	&dev_attr_vbe_modes.attr,
	&dev_attr_oem_venकरोr.attr,
	&dev_attr_oem_product_name.attr,
	&dev_attr_oem_product_rev.attr,
	&dev_attr_oem_string.attr,
	&dev_attr_nocrtc.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group uvesafb_dev_attgrp = अणु
	.name = शून्य,
	.attrs = uvesafb_dev_attrs,
पूर्ण;

अटल पूर्णांक uvesafb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा vbe_mode_ib *mode = शून्य;
	काष्ठा uvesafb_par *par;
	पूर्णांक err = 0, i;

	info = framebuffer_alloc(माप(*par) +	माप(u32) * 256, &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;

	err = uvesafb_vbe_init(info);
	अगर (err) अणु
		pr_err("vbe_init() failed with %d\n", err);
		जाओ out;
	पूर्ण

	info->fbops = &uvesafb_ops;

	i = uvesafb_vbe_init_mode(info);
	अगर (i < 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		mode = &par->vbe_modes[i];
	पूर्ण

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		err = -ENXIO;
		जाओ out;
	पूर्ण

	uvesafb_init_info(info, mode);

	अगर (!request_region(0x3c0, 32, "uvesafb")) अणु
		pr_err("request region 0x3c0-0x3e0 failed\n");
		err = -EIO;
		जाओ out_mode;
	पूर्ण

	अगर (!request_mem_region(info->fix.smem_start, info->fix.smem_len,
				"uvesafb")) अणु
		pr_err("cannot reserve video memory at 0x%lx\n",
		       info->fix.smem_start);
		err = -EIO;
		जाओ out_reg;
	पूर्ण

	uvesafb_init_mtrr(info);
	uvesafb_ioremap(info);

	अगर (!info->screen_base) अणु
		pr_err("abort, cannot ioremap 0x%x bytes of video memory at 0x%lx\n",
		       info->fix.smem_len, info->fix.smem_start);
		err = -EIO;
		जाओ out_mem;
	पूर्ण

	platक्रमm_set_drvdata(dev, info);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		pr_err("failed to register framebuffer device\n");
		err = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	pr_info("framebuffer at 0x%lx, mapped to 0x%p, using %dk, total %dk\n",
		info->fix.smem_start, info->screen_base,
		info->fix.smem_len / 1024, par->vbe_ib.total_memory * 64);
	fb_info(info, "%s frame buffer device\n", info->fix.id);

	err = sysfs_create_group(&dev->dev.kobj, &uvesafb_dev_attgrp);
	अगर (err != 0)
		fb_warn(info, "failed to register attributes\n");

	वापस 0;

out_unmap:
	iounmap(info->screen_base);
out_mem:
	release_mem_region(info->fix.smem_start, info->fix.smem_len);
out_reg:
	release_region(0x3c0, 32);
out_mode:
	अगर (!list_empty(&info->modelist))
		fb_destroy_modelist(&info->modelist);
	fb_destroy_modedb(info->monspecs.modedb);
	fb_dealloc_cmap(&info->cmap);
out:
	kमुक्त(par->vbe_modes);

	framebuffer_release(info);
	वापस err;
पूर्ण

अटल पूर्णांक uvesafb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा uvesafb_par *par = info->par;

		sysfs_हटाओ_group(&dev->dev.kobj, &uvesafb_dev_attgrp);
		unरेजिस्टर_framebuffer(info);
		release_region(0x3c0, 32);
		iounmap(info->screen_base);
		arch_phys_wc_del(par->mtrr_handle);
		release_mem_region(info->fix.smem_start, info->fix.smem_len);
		fb_destroy_modedb(info->monspecs.modedb);
		fb_dealloc_cmap(&info->cmap);

		kमुक्त(par->vbe_modes);
		kमुक्त(par->vbe_state_orig);
		kमुक्त(par->vbe_state_saved);

		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver uvesafb_driver = अणु
	.probe  = uvesafb_probe,
	.हटाओ = uvesafb_हटाओ,
	.driver = अणु
		.name = "uvesafb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *uvesafb_device;

#अगर_अघोषित MODULE
अटल पूर्णांक uvesafb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt) जारी;

		अगर (!म_भेद(this_opt, "redraw"))
			ypan = 0;
		अन्यथा अगर (!म_भेद(this_opt, "ypan"))
			ypan = 1;
		अन्यथा अगर (!म_भेद(this_opt, "ywrap"))
			ypan = 2;
		अन्यथा अगर (!म_भेद(this_opt, "vgapal"))
			pmi_setpal = false;
		अन्यथा अगर (!म_भेद(this_opt, "pmipal"))
			pmi_setpal = true;
		अन्यथा अगर (!म_भेदन(this_opt, "mtrr:", 5))
			mtrr = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		अन्यथा अगर (!म_भेद(this_opt, "nomtrr"))
			mtrr = 0;
		अन्यथा अगर (!म_भेद(this_opt, "nocrtc"))
			nocrtc = true;
		अन्यथा अगर (!म_भेद(this_opt, "noedid"))
			noedid = true;
		अन्यथा अगर (!म_भेद(this_opt, "noblank"))
			blank = false;
		अन्यथा अगर (!म_भेदन(this_opt, "vtotal:", 7))
			vram_total = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vremap:", 7))
			vram_remap = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "maxhf:", 6))
			maxhf = simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "maxvf:", 6))
			maxvf = simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "maxclk:", 7))
			maxclk = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "vbemode:", 8))
			vbemode = simple_म_से_अदीर्घ(this_opt + 8, शून्य, 0);
		अन्यथा अगर (this_opt[0] >= '0' && this_opt[0] <= '9') अणु
			mode_option = this_opt;
		पूर्ण अन्यथा अणु
			pr_warn("unrecognized option %s\n", this_opt);
		पूर्ण
	पूर्ण

	अगर (mtrr != 3 && mtrr != 0)
		pr_warn("uvesafb: mtrr should be set to 0 or 3; %d is unsupported", mtrr);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* !MODULE */

अटल sमाप_प्रकार v86d_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", v86d_path);
पूर्ण

अटल sमाप_प्रकार v86d_store(काष्ठा device_driver *dev, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	म_नकलन(v86d_path, buf, PATH_MAX - 1);
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(v86d);

अटल पूर्णांक uvesafb_init(व्योम)
अणु
	पूर्णांक err;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("uvesafb", &option))
		वापस -ENODEV;
	uvesafb_setup(option);
#पूर्ण_अगर
	err = cn_add_callback(&uvesafb_cn_id, "uvesafb", uvesafb_cn_callback);
	अगर (err)
		वापस err;

	err = platक्रमm_driver_रेजिस्टर(&uvesafb_driver);

	अगर (!err) अणु
		uvesafb_device = platक्रमm_device_alloc("uvesafb", 0);
		अगर (uvesafb_device)
			err = platक्रमm_device_add(uvesafb_device);
		अन्यथा
			err = -ENOMEM;

		अगर (err) अणु
			platक्रमm_device_put(uvesafb_device);
			platक्रमm_driver_unरेजिस्टर(&uvesafb_driver);
			cn_del_callback(&uvesafb_cn_id);
			वापस err;
		पूर्ण

		err = driver_create_file(&uvesafb_driver.driver,
				&driver_attr_v86d);
		अगर (err) अणु
			pr_warn("failed to register attributes\n");
			err = 0;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

module_init(uvesafb_init);

अटल व्योम uvesafb_निकास(व्योम)
अणु
	काष्ठा uvesafb_ktask *task;

	अगर (v86d_started) अणु
		task = uvesafb_prep();
		अगर (task) अणु
			task->t.flags = TF_EXIT;
			uvesafb_exec(task);
			uvesafb_मुक्त(task);
		पूर्ण
	पूर्ण

	cn_del_callback(&uvesafb_cn_id);
	driver_हटाओ_file(&uvesafb_driver.driver, &driver_attr_v86d);
	platक्रमm_device_unरेजिस्टर(uvesafb_device);
	platक्रमm_driver_unरेजिस्टर(&uvesafb_driver);
पूर्ण

module_निकास(uvesafb_निकास);

अटल पूर्णांक param_set_scroll(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	ypan = 0;

	अगर (!म_भेद(val, "redraw"))
		ypan = 0;
	अन्यथा अगर (!म_भेद(val, "ypan"))
		ypan = 1;
	अन्यथा अगर (!म_भेद(val, "ywrap"))
		ypan = 2;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा kernel_param_ops param_ops_scroll = अणु
	.set = param_set_scroll,
पूर्ण;
#घोषणा param_check_scroll(name, p) __param_check(name, p, व्योम)

module_param_named(scroll, ypan, scroll, 0);
MODULE_PARM_DESC(scroll,
	"Scrolling mode, set to 'redraw', 'ypan', or 'ywrap'");
module_param_named(vgapal, pmi_setpal, invbool, 0);
MODULE_PARM_DESC(vgapal, "Set palette using VGA registers");
module_param_named(pmipal, pmi_setpal, bool, 0);
MODULE_PARM_DESC(pmipal, "Set palette using PMI calls");
module_param(mtrr, uपूर्णांक, 0);
MODULE_PARM_DESC(mtrr,
	"Memory Type Range Registers setting. Use 0 to disable.");
module_param(blank, bool, 0);
MODULE_PARM_DESC(blank, "Enable hardware blanking");
module_param(nocrtc, bool, 0);
MODULE_PARM_DESC(nocrtc, "Ignore CRTC timings when setting modes");
module_param(noedid, bool, 0);
MODULE_PARM_DESC(noedid,
	"Ignore EDID-provided monitor limits when setting modes");
module_param(vram_remap, uपूर्णांक, 0);
MODULE_PARM_DESC(vram_remap, "Set amount of video memory to be used [MiB]");
module_param(vram_total, uपूर्णांक, 0);
MODULE_PARM_DESC(vram_total, "Set total amount of video memory [MiB]");
module_param(maxclk, uलघु, 0);
MODULE_PARM_DESC(maxclk, "Maximum pixelclock [MHz], overrides EDID data");
module_param(maxhf, uलघु, 0);
MODULE_PARM_DESC(maxhf,
	"Maximum horizontal frequency [kHz], overrides EDID data");
module_param(maxvf, uलघु, 0);
MODULE_PARM_DESC(maxvf,
	"Maximum vertical frequency [Hz], overrides EDID data");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option,
	"Specify initial video mode as \"<xres>x<yres>[-<bpp>][@<refresh>]\"");
module_param(vbemode, uलघु, 0);
MODULE_PARM_DESC(vbemode,
	"VBE mode number to set, overrides the 'mode' option");
module_param_string(v86d, v86d_path, PATH_MAX, 0660);
MODULE_PARM_DESC(v86d, "Path to the v86d userspace helper.");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Januszewski <spock@gentoo.org>");
MODULE_DESCRIPTION("Framebuffer driver for VBE2.0+ compliant graphics boards");

