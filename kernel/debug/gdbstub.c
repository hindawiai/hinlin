<शैली गुरु>
/*
 * Kernel Debug Core
 *
 * Maपूर्णांकainer: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (C) 2000-2001 VERITAS Software Corporation.
 * Copyright (C) 2002-2004 Timesys Corporation
 * Copyright (C) 2003-2004 Amit S. Kale <amitkale@linsyssoft.com>
 * Copyright (C) 2004 Pavel Machek <pavel@ucw.cz>
 * Copyright (C) 2004-2006 Tom Rini <trini@kernel.crashing.org>
 * Copyright (C) 2004-2006 LinSysSoft Technologies Pvt. Ltd.
 * Copyright (C) 2005-2009 Wind River Systems, Inc.
 * Copyright (C) 2007 MontaVista Software, Inc.
 * Copyright (C) 2008 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Contributors at various stages not listed above:
 *  Jason Wessel ( jason.wessel@windriver.com )
 *  George Anzinger <george@mvista.com>
 *  Anurekh Saxena (anurekh.saxena@बारys.com)
 *  Lake Stevens Instrument Division (Glenn Engel)
 *  Jim Kingकरोn, Cygnus Support.
 *
 * Original KGDB stub: David Grothe <dave@gcom.com>,
 * Tigran Aivazian <tigran@sco.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/reboot.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "debug_core.h"

#घोषणा KGDB_MAX_THREAD_QUERY 17

/* Our I/O buffers. */
अटल अक्षर			remcom_in_buffer[BUFMAX];
अटल अक्षर			remcom_out_buffer[BUFMAX];
अटल पूर्णांक			gdbstub_use_prev_in_buf;
अटल पूर्णांक			gdbstub_prev_in_buf_pos;

/* Storage क्रम the रेजिस्टरs, in GDB क्रमmat. */
अटल अचिन्हित दीर्घ		gdb_regs[(NUMREGBYTES +
					माप(अचिन्हित दीर्घ) - 1) /
					माप(अचिन्हित दीर्घ)];

/*
 * GDB remote protocol parser:
 */

#अगर_घोषित CONFIG_KGDB_KDB
अटल पूर्णांक gdbstub_पढ़ो_रुको(व्योम)
अणु
	पूर्णांक ret = -1;
	पूर्णांक i;

	अगर (unlikely(gdbstub_use_prev_in_buf)) अणु
		अगर (gdbstub_prev_in_buf_pos < gdbstub_use_prev_in_buf)
			वापस remcom_in_buffer[gdbstub_prev_in_buf_pos++];
		अन्यथा
			gdbstub_use_prev_in_buf = 0;
	पूर्ण

	/* poll any additional I/O पूर्णांकerfaces that are defined */
	जबतक (ret < 0)
		क्रम (i = 0; kdb_poll_funcs[i] != शून्य; i++) अणु
			ret = kdb_poll_funcs[i]();
			अगर (ret > 0)
				अवरोध;
		पूर्ण
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक gdbstub_पढ़ो_रुको(व्योम)
अणु
	पूर्णांक ret = dbg_io_ops->पढ़ो_अक्षर();
	जबतक (ret == NO_POLL_CHAR)
		ret = dbg_io_ops->पढ़ो_अक्षर();
	वापस ret;
पूर्ण
#पूर्ण_अगर
/* scan क्रम the sequence $<data>#<checksum> */
अटल व्योम get_packet(अक्षर *buffer)
अणु
	अचिन्हित अक्षर checksum;
	अचिन्हित अक्षर xmitcsum;
	पूर्णांक count;
	अक्षर ch;

	करो अणु
		/*
		 * Spin and रुको around क्रम the start अक्षरacter, ignore all
		 * other अक्षरacters:
		 */
		जबतक ((ch = (gdbstub_पढ़ो_रुको())) != '$')
			/* nothing */;

		kgdb_connected = 1;
		checksum = 0;
		xmitcsum = -1;

		count = 0;

		/*
		 * now, पढ़ो until a # or end of buffer is found:
		 */
		जबतक (count < (BUFMAX - 1)) अणु
			ch = gdbstub_पढ़ो_रुको();
			अगर (ch == '#')
				अवरोध;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		पूर्ण

		अगर (ch == '#') अणु
			xmitcsum = hex_to_bin(gdbstub_पढ़ो_रुको()) << 4;
			xmitcsum += hex_to_bin(gdbstub_पढ़ो_रुको());

			अगर (checksum != xmitcsum)
				/* failed checksum */
				dbg_io_ops->ग_लिखो_अक्षर('-');
			अन्यथा
				/* successful transfer */
				dbg_io_ops->ग_लिखो_अक्षर('+');
			अगर (dbg_io_ops->flush)
				dbg_io_ops->flush();
		पूर्ण
		buffer[count] = 0;
	पूर्ण जबतक (checksum != xmitcsum);
पूर्ण

/*
 * Send the packet in buffer.
 * Check क्रम gdb connection अगर asked क्रम.
 */
अटल व्योम put_packet(अक्षर *buffer)
अणु
	अचिन्हित अक्षर checksum;
	पूर्णांक count;
	अक्षर ch;

	/*
	 * $<packet info>#<checksum>.
	 */
	जबतक (1) अणु
		dbg_io_ops->ग_लिखो_अक्षर('$');
		checksum = 0;
		count = 0;

		जबतक ((ch = buffer[count])) अणु
			dbg_io_ops->ग_लिखो_अक्षर(ch);
			checksum += ch;
			count++;
		पूर्ण

		dbg_io_ops->ग_लिखो_अक्षर('#');
		dbg_io_ops->ग_लिखो_अक्षर(hex_asc_hi(checksum));
		dbg_io_ops->ग_लिखो_अक्षर(hex_asc_lo(checksum));
		अगर (dbg_io_ops->flush)
			dbg_io_ops->flush();

		/* Now see what we get in reply. */
		ch = gdbstub_पढ़ो_रुको();

		अगर (ch == 3)
			ch = gdbstub_पढ़ो_रुको();

		/* If we get an ACK, we are करोne. */
		अगर (ch == '+')
			वापस;

		/*
		 * If we get the start of another packet, this means
		 * that GDB is attempting to reconnect.  We will NAK
		 * the packet being sent, and stop trying to send this
		 * packet.
		 */
		अगर (ch == '$') अणु
			dbg_io_ops->ग_लिखो_अक्षर('-');
			अगर (dbg_io_ops->flush)
				dbg_io_ops->flush();
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर gdbmsgbuf[BUFMAX + 1];

व्योम gdbstub_msg_ग_लिखो(स्थिर अक्षर *s, पूर्णांक len)
अणु
	अक्षर *bufptr;
	पूर्णांक wcount;
	पूर्णांक i;

	अगर (len == 0)
		len = म_माप(s);

	/* 'O'utput */
	gdbmsgbuf[0] = 'O';

	/* Fill and send buffers... */
	जबतक (len > 0) अणु
		bufptr = gdbmsgbuf + 1;

		/* Calculate how many this समय */
		अगर ((len << 1) > (BUFMAX - 2))
			wcount = (BUFMAX - 2) >> 1;
		अन्यथा
			wcount = len;

		/* Pack in hex अक्षरs */
		क्रम (i = 0; i < wcount; i++)
			bufptr = hex_byte_pack(bufptr, s[i]);
		*bufptr = '\0';

		/* Move up */
		s += wcount;
		len -= wcount;

		/* Write packet */
		put_packet(gdbmsgbuf);
	पूर्ण
पूर्ण

/*
 * Convert the memory poपूर्णांकed to by mem पूर्णांकo hex, placing result in
 * buf.  Return a poपूर्णांकer to the last अक्षर put in buf (null). May
 * वापस an error.
 */
अक्षर *kgdb_mem2hex(अक्षर *mem, अक्षर *buf, पूर्णांक count)
अणु
	अक्षर *पंचांगp;
	पूर्णांक err;

	/*
	 * We use the upper half of buf as an पूर्णांकermediate buffer क्रम the
	 * raw memory copy.  Hex conversion will work against this one.
	 */
	पंचांगp = buf + count;

	err = copy_from_kernel_nofault(पंचांगp, mem, count);
	अगर (err)
		वापस शून्य;
	जबतक (count > 0) अणु
		buf = hex_byte_pack(buf, *पंचांगp);
		पंचांगp++;
		count--;
	पूर्ण
	*buf = 0;

	वापस buf;
पूर्ण

/*
 * Convert the hex array poपूर्णांकed to by buf पूर्णांकo binary to be placed in
 * mem.  Return a poपूर्णांकer to the अक्षरacter AFTER the last byte
 * written.  May वापस an error.
 */
पूर्णांक kgdb_hex2mem(अक्षर *buf, अक्षर *mem, पूर्णांक count)
अणु
	अक्षर *पंचांगp_raw;
	अक्षर *पंचांगp_hex;

	/*
	 * We use the upper half of buf as an पूर्णांकermediate buffer क्रम the
	 * raw memory that is converted from hex.
	 */
	पंचांगp_raw = buf + count * 2;

	पंचांगp_hex = पंचांगp_raw - 1;
	जबतक (पंचांगp_hex >= buf) अणु
		पंचांगp_raw--;
		*पंचांगp_raw = hex_to_bin(*पंचांगp_hex--);
		*पंचांगp_raw |= hex_to_bin(*पंचांगp_hex--) << 4;
	पूर्ण

	वापस copy_to_kernel_nofault(mem, पंचांगp_raw, count);
पूर्ण

/*
 * While we find nice hex अक्षरs, build a दीर्घ_val.
 * Return number of अक्षरs processed.
 */
पूर्णांक kgdb_hex2दीर्घ(अक्षर **ptr, अचिन्हित दीर्घ *दीर्घ_val)
अणु
	पूर्णांक hex_val;
	पूर्णांक num = 0;
	पूर्णांक negate = 0;

	*दीर्घ_val = 0;

	अगर (**ptr == '-') अणु
		negate = 1;
		(*ptr)++;
	पूर्ण
	जबतक (**ptr) अणु
		hex_val = hex_to_bin(**ptr);
		अगर (hex_val < 0)
			अवरोध;

		*दीर्घ_val = (*दीर्घ_val << 4) | hex_val;
		num++;
		(*ptr)++;
	पूर्ण

	अगर (negate)
		*दीर्घ_val = -*दीर्घ_val;

	वापस num;
पूर्ण

/*
 * Copy the binary array poपूर्णांकed to by buf पूर्णांकo mem.  Fix $, #, and
 * 0x7d escaped with 0x7d. Return -EFAULT on failure or 0 on success.
 * The input buf is overwritten with the result to ग_लिखो to mem.
 */
अटल पूर्णांक kgdb_ebin2mem(अक्षर *buf, अक्षर *mem, पूर्णांक count)
अणु
	पूर्णांक size = 0;
	अक्षर *c = buf;

	जबतक (count-- > 0) अणु
		c[size] = *buf++;
		अगर (c[size] == 0x7d)
			c[size] = *buf++ ^ 0x20;
		size++;
	पूर्ण

	वापस copy_to_kernel_nofault(mem, c, size);
पूर्ण

#अगर DBG_MAX_REG_NUM > 0
व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	पूर्णांक idx = 0;
	अक्षर *ptr = (अक्षर *)gdb_regs;

	क्रम (i = 0; i < DBG_MAX_REG_NUM; i++) अणु
		dbg_get_reg(i, ptr + idx, regs);
		idx += dbg_reg_def[i].size;
	पूर्ण
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	पूर्णांक idx = 0;
	अक्षर *ptr = (अक्षर *)gdb_regs;

	क्रम (i = 0; i < DBG_MAX_REG_NUM; i++) अणु
		dbg_set_reg(i, ptr + idx, regs);
		idx += dbg_reg_def[i].size;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* DBG_MAX_REG_NUM > 0 */

/* Write memory due to an 'M' or 'X' packet. */
अटल पूर्णांक ग_लिखो_mem_msg(पूर्णांक binary)
अणु
	अक्षर *ptr = &remcom_in_buffer[1];
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ length;
	पूर्णांक err;

	अगर (kgdb_hex2दीर्घ(&ptr, &addr) > 0 && *(ptr++) == ',' &&
	    kgdb_hex2दीर्घ(&ptr, &length) > 0 && *(ptr++) == ':') अणु
		अगर (binary)
			err = kgdb_ebin2mem(ptr, (अक्षर *)addr, length);
		अन्यथा
			err = kgdb_hex2mem(ptr, (अक्षर *)addr, length);
		अगर (err)
			वापस err;
		अगर (CACHE_FLUSH_IS_SAFE)
			flush_icache_range(addr, addr + length);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम error_packet(अक्षर *pkt, पूर्णांक error)
अणु
	error = -error;
	pkt[0] = 'E';
	pkt[1] = hex_asc[(error / 10)];
	pkt[2] = hex_asc[(error % 10)];
	pkt[3] = '\0';
पूर्ण

/*
 * Thपढ़ो ID accessors. We represent a flat TID space to GDB, where
 * the per CPU idle thपढ़ोs (which under Linux all have PID 0) are
 * remapped to negative TIDs.
 */

#घोषणा BUF_THREAD_ID_SIZE	8

अटल अक्षर *pack_thपढ़ोid(अक्षर *pkt, अचिन्हित अक्षर *id)
अणु
	अचिन्हित अक्षर *limit;
	पूर्णांक lzero = 1;

	limit = id + (BUF_THREAD_ID_SIZE / 2);
	जबतक (id < limit) अणु
		अगर (!lzero || *id != 0) अणु
			pkt = hex_byte_pack(pkt, *id);
			lzero = 0;
		पूर्ण
		id++;
	पूर्ण

	अगर (lzero)
		pkt = hex_byte_pack(pkt, 0);

	वापस pkt;
पूर्ण

अटल व्योम पूर्णांक_to_thपढ़ोref(अचिन्हित अक्षर *id, पूर्णांक value)
अणु
	put_unaligned_be32(value, id);
पूर्ण

अटल काष्ठा task_काष्ठा *getthपढ़ो(काष्ठा pt_regs *regs, पूर्णांक tid)
अणु
	/*
	 * Non-positive TIDs are remapped to the cpu shaकरोw inक्रमmation
	 */
	अगर (tid == 0 || tid == -1)
		tid = -atomic_पढ़ो(&kgdb_active) - 2;
	अगर (tid < -1 && tid > -NR_CPUS - 2) अणु
		अगर (kgdb_info[-tid - 2].task)
			वापस kgdb_info[-tid - 2].task;
		अन्यथा
			वापस idle_task(-tid - 2);
	पूर्ण
	अगर (tid <= 0) अणु
		prपूर्णांकk(KERN_ERR "KGDB: Internal thread select error\n");
		dump_stack();
		वापस शून्य;
	पूर्ण

	/*
	 * find_task_by_pid_ns() करोes not take the tasklist lock anymore
	 * but is nicely RCU locked - hence is a pretty resilient
	 * thing to use:
	 */
	वापस find_task_by_pid_ns(tid, &init_pid_ns);
पूर्ण


/*
 * Remap normal tasks to their real PID,
 * CPU shaकरोw thपढ़ोs are mapped to -CPU - 2
 */
अटल अंतरभूत पूर्णांक shaकरोw_pid(पूर्णांक realpid)
अणु
	अगर (realpid)
		वापस realpid;

	वापस -raw_smp_processor_id() - 2;
पूर्ण

/*
 * All the functions that start with gdb_cmd are the various
 * operations to implement the handlers क्रम the gdbserial protocol
 * where KGDB is communicating with an बाह्यal debugger
 */

/* Handle the '?' status packets */
अटल व्योम gdb_cmd_status(काष्ठा kgdb_state *ks)
अणु
	/*
	 * We know that this packet is only sent
	 * during initial connect.  So to be safe,
	 * we clear out our अवरोधpoपूर्णांकs now in हाल
	 * GDB is reconnecting.
	 */
	dbg_हटाओ_all_अवरोध();

	remcom_out_buffer[0] = 'S';
	hex_byte_pack(&remcom_out_buffer[1], ks->signo);
पूर्ण

अटल व्योम gdb_get_regs_helper(काष्ठा kgdb_state *ks)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	व्योम *local_debuggerinfo;
	पूर्णांक i;

	thपढ़ो = kgdb_usethपढ़ो;
	अगर (!thपढ़ो) अणु
		thपढ़ो = kgdb_info[ks->cpu].task;
		local_debuggerinfo = kgdb_info[ks->cpu].debuggerinfo;
	पूर्ण अन्यथा अणु
		local_debuggerinfo = शून्य;
		क्रम_each_online_cpu(i) अणु
			/*
			 * Try to find the task on some other
			 * or possibly this node अगर we करो not
			 * find the matching task then we try
			 * to approximate the results.
			 */
			अगर (thपढ़ो == kgdb_info[i].task)
				local_debuggerinfo = kgdb_info[i].debuggerinfo;
		पूर्ण
	पूर्ण

	/*
	 * All thपढ़ोs that करोn't have debuggerinfo should be
	 * in schedule() sleeping, since all other CPUs
	 * are in kgdb_रुको, and thus have debuggerinfo.
	 */
	अगर (local_debuggerinfo) अणु
		pt_regs_to_gdb_regs(gdb_regs, local_debuggerinfo);
	पूर्ण अन्यथा अणु
		/*
		 * Pull stuff saved during चयन_to; nothing
		 * अन्यथा is accessible (or even particularly
		 * relevant).
		 *
		 * This should be enough क्रम a stack trace.
		 */
		sleeping_thपढ़ो_to_gdb_regs(gdb_regs, thपढ़ो);
	पूर्ण
पूर्ण

/* Handle the 'g' get रेजिस्टरs request */
अटल व्योम gdb_cmd_getregs(काष्ठा kgdb_state *ks)
अणु
	gdb_get_regs_helper(ks);
	kgdb_mem2hex((अक्षर *)gdb_regs, remcom_out_buffer, NUMREGBYTES);
पूर्ण

/* Handle the 'G' set रेजिस्टरs request */
अटल व्योम gdb_cmd_setregs(काष्ठा kgdb_state *ks)
अणु
	kgdb_hex2mem(&remcom_in_buffer[1], (अक्षर *)gdb_regs, NUMREGBYTES);

	अगर (kgdb_usethपढ़ो && kgdb_usethपढ़ो != current) अणु
		error_packet(remcom_out_buffer, -EINVAL);
	पूर्ण अन्यथा अणु
		gdb_regs_to_pt_regs(gdb_regs, ks->linux_regs);
		म_नकल(remcom_out_buffer, "OK");
	पूर्ण
पूर्ण

/* Handle the 'm' memory पढ़ो bytes */
अटल व्योम gdb_cmd_memपढ़ो(काष्ठा kgdb_state *ks)
अणु
	अक्षर *ptr = &remcom_in_buffer[1];
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ addr;
	अक्षर *err;

	अगर (kgdb_hex2दीर्घ(&ptr, &addr) > 0 && *ptr++ == ',' &&
					kgdb_hex2दीर्घ(&ptr, &length) > 0) अणु
		err = kgdb_mem2hex((अक्षर *)addr, remcom_out_buffer, length);
		अगर (!err)
			error_packet(remcom_out_buffer, -EINVAL);
	पूर्ण अन्यथा अणु
		error_packet(remcom_out_buffer, -EINVAL);
	पूर्ण
पूर्ण

/* Handle the 'M' memory ग_लिखो bytes */
अटल व्योम gdb_cmd_memग_लिखो(काष्ठा kgdb_state *ks)
अणु
	पूर्णांक err = ग_लिखो_mem_msg(0);

	अगर (err)
		error_packet(remcom_out_buffer, err);
	अन्यथा
		म_नकल(remcom_out_buffer, "OK");
पूर्ण

#अगर DBG_MAX_REG_NUM > 0
अटल अक्षर *gdb_hex_reg_helper(पूर्णांक regnum, अक्षर *out)
अणु
	पूर्णांक i;
	पूर्णांक offset = 0;

	क्रम (i = 0; i < regnum; i++)
		offset += dbg_reg_def[i].size;
	वापस kgdb_mem2hex((अक्षर *)gdb_regs + offset, out,
			    dbg_reg_def[i].size);
पूर्ण

/* Handle the 'p' inभागidual रेजिस्टर get */
अटल व्योम gdb_cmd_reg_get(काष्ठा kgdb_state *ks)
अणु
	अचिन्हित दीर्घ regnum;
	अक्षर *ptr = &remcom_in_buffer[1];

	kgdb_hex2दीर्घ(&ptr, &regnum);
	अगर (regnum >= DBG_MAX_REG_NUM) अणु
		error_packet(remcom_out_buffer, -EINVAL);
		वापस;
	पूर्ण
	gdb_get_regs_helper(ks);
	gdb_hex_reg_helper(regnum, remcom_out_buffer);
पूर्ण

/* Handle the 'P' inभागidual रेजिस्टर set */
अटल व्योम gdb_cmd_reg_set(काष्ठा kgdb_state *ks)
अणु
	अचिन्हित दीर्घ regnum;
	अक्षर *ptr = &remcom_in_buffer[1];
	पूर्णांक i = 0;

	kgdb_hex2दीर्घ(&ptr, &regnum);
	अगर (*ptr++ != '=' ||
	    !(!kgdb_usethपढ़ो || kgdb_usethपढ़ो == current) ||
	    !dbg_get_reg(regnum, gdb_regs, ks->linux_regs)) अणु
		error_packet(remcom_out_buffer, -EINVAL);
		वापस;
	पूर्ण
	स_रखो(gdb_regs, 0, माप(gdb_regs));
	जबतक (i < माप(gdb_regs) * 2)
		अगर (hex_to_bin(ptr[i]) >= 0)
			i++;
		अन्यथा
			अवरोध;
	i = i / 2;
	kgdb_hex2mem(ptr, (अक्षर *)gdb_regs, i);
	dbg_set_reg(regnum, gdb_regs, ks->linux_regs);
	म_नकल(remcom_out_buffer, "OK");
पूर्ण
#पूर्ण_अगर /* DBG_MAX_REG_NUM > 0 */

/* Handle the 'X' memory binary ग_लिखो bytes */
अटल व्योम gdb_cmd_binग_लिखो(काष्ठा kgdb_state *ks)
अणु
	पूर्णांक err = ग_लिखो_mem_msg(1);

	अगर (err)
		error_packet(remcom_out_buffer, err);
	अन्यथा
		म_नकल(remcom_out_buffer, "OK");
पूर्ण

/* Handle the 'D' or 'k', detach or समाप्त packets */
अटल व्योम gdb_cmd_detachसमाप्त(काष्ठा kgdb_state *ks)
अणु
	पूर्णांक error;

	/* The detach हाल */
	अगर (remcom_in_buffer[0] == 'D') अणु
		error = dbg_हटाओ_all_अवरोध();
		अगर (error < 0) अणु
			error_packet(remcom_out_buffer, error);
		पूर्ण अन्यथा अणु
			म_नकल(remcom_out_buffer, "OK");
			kgdb_connected = 0;
		पूर्ण
		put_packet(remcom_out_buffer);
	पूर्ण अन्यथा अणु
		/*
		 * Assume the समाप्त हाल, with no निकास code checking,
		 * trying to क्रमce detach the debugger:
		 */
		dbg_हटाओ_all_अवरोध();
		kgdb_connected = 0;
	पूर्ण
पूर्ण

/* Handle the 'R' reboot packets */
अटल पूर्णांक gdb_cmd_reboot(काष्ठा kgdb_state *ks)
अणु
	/* For now, only honor R0 */
	अगर (म_भेद(remcom_in_buffer, "R0") == 0) अणु
		prपूर्णांकk(KERN_CRIT "Executing emergency reboot\n");
		म_नकल(remcom_out_buffer, "OK");
		put_packet(remcom_out_buffer);

		/*
		 * Execution should not वापस from
		 * machine_emergency_restart()
		 */
		machine_emergency_restart();
		kgdb_connected = 0;

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Handle the 'q' query packets */
अटल व्योम gdb_cmd_query(काष्ठा kgdb_state *ks)
अणु
	काष्ठा task_काष्ठा *g;
	काष्ठा task_काष्ठा *p;
	अचिन्हित अक्षर thref[BUF_THREAD_ID_SIZE];
	अक्षर *ptr;
	पूर्णांक i;
	पूर्णांक cpu;
	पूर्णांक finished = 0;

	चयन (remcom_in_buffer[1]) अणु
	हाल 's':
	हाल 'f':
		अगर (स_भेद(remcom_in_buffer + 2, "ThreadInfo", 10))
			अवरोध;

		i = 0;
		remcom_out_buffer[0] = 'm';
		ptr = remcom_out_buffer + 1;
		अगर (remcom_in_buffer[1] == 'f') अणु
			/* Each cpu is a shaकरोw thपढ़ो */
			क्रम_each_online_cpu(cpu) अणु
				ks->thr_query = 0;
				पूर्णांक_to_thपढ़ोref(thref, -cpu - 2);
				ptr = pack_thपढ़ोid(ptr, thref);
				*(ptr++) = ',';
				i++;
			पूर्ण
		पूर्ण

		क्रम_each_process_thपढ़ो(g, p) अणु
			अगर (i >= ks->thr_query && !finished) अणु
				पूर्णांक_to_thपढ़ोref(thref, p->pid);
				ptr = pack_thपढ़ोid(ptr, thref);
				*(ptr++) = ',';
				ks->thr_query++;
				अगर (ks->thr_query % KGDB_MAX_THREAD_QUERY == 0)
					finished = 1;
			पूर्ण
			i++;
		पूर्ण

		*(--ptr) = '\0';
		अवरोध;

	हाल 'C':
		/* Current thपढ़ो id */
		म_नकल(remcom_out_buffer, "QC");
		ks->thपढ़ोid = shaकरोw_pid(current->pid);
		पूर्णांक_to_thपढ़ोref(thref, ks->thपढ़ोid);
		pack_thपढ़ोid(remcom_out_buffer + 2, thref);
		अवरोध;
	हाल 'T':
		अगर (स_भेद(remcom_in_buffer + 1, "ThreadExtraInfo,", 16))
			अवरोध;

		ks->thपढ़ोid = 0;
		ptr = remcom_in_buffer + 17;
		kgdb_hex2दीर्घ(&ptr, &ks->thपढ़ोid);
		अगर (!getthपढ़ो(ks->linux_regs, ks->thपढ़ोid)) अणु
			error_packet(remcom_out_buffer, -EINVAL);
			अवरोध;
		पूर्ण
		अगर ((पूर्णांक)ks->thपढ़ोid > 0) अणु
			kgdb_mem2hex(getthपढ़ो(ks->linux_regs,
					ks->thपढ़ोid)->comm,
					remcom_out_buffer, 16);
		पूर्ण अन्यथा अणु
			अटल अक्षर पंचांगpstr[23 + BUF_THREAD_ID_SIZE];

			प्र_लिखो(पंचांगpstr, "shadowCPU%d",
					(पूर्णांक)(-ks->thपढ़ोid - 2));
			kgdb_mem2hex(पंचांगpstr, remcom_out_buffer, म_माप(पंचांगpstr));
		पूर्ण
		अवरोध;
#अगर_घोषित CONFIG_KGDB_KDB
	हाल 'R':
		अगर (म_भेदन(remcom_in_buffer, "qRcmd,", 6) == 0) अणु
			पूर्णांक len = म_माप(remcom_in_buffer + 6);

			अगर ((len % 2) != 0) अणु
				म_नकल(remcom_out_buffer, "E01");
				अवरोध;
			पूर्ण
			kgdb_hex2mem(remcom_in_buffer + 6,
				     remcom_out_buffer, len);
			len = len / 2;
			remcom_out_buffer[len++] = 0;

			kdb_common_init_state(ks);
			kdb_parse(remcom_out_buffer);
			kdb_common_deinit_state();

			म_नकल(remcom_out_buffer, "OK");
		पूर्ण
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_ARCH_KGDB_QXFER_PKT
	हाल 'S':
		अगर (!म_भेदन(remcom_in_buffer, "qSupported:", 11))
			म_नकल(remcom_out_buffer, kgdb_arch_gdb_stub_feature);
		अवरोध;
	हाल 'X':
		अगर (!म_भेदन(remcom_in_buffer, "qXfer:", 6))
			kgdb_arch_handle_qxfer_pkt(remcom_in_buffer,
						   remcom_out_buffer);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* Handle the 'H' task query packets */
अटल व्योम gdb_cmd_task(काष्ठा kgdb_state *ks)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	अक्षर *ptr;

	चयन (remcom_in_buffer[1]) अणु
	हाल 'g':
		ptr = &remcom_in_buffer[2];
		kgdb_hex2दीर्घ(&ptr, &ks->thपढ़ोid);
		thपढ़ो = getthपढ़ो(ks->linux_regs, ks->thपढ़ोid);
		अगर (!thपढ़ो && ks->thपढ़ोid > 0) अणु
			error_packet(remcom_out_buffer, -EINVAL);
			अवरोध;
		पूर्ण
		kgdb_usethपढ़ो = thपढ़ो;
		ks->kgdb_usethपढ़ोid = ks->thपढ़ोid;
		म_नकल(remcom_out_buffer, "OK");
		अवरोध;
	हाल 'c':
		ptr = &remcom_in_buffer[2];
		kgdb_hex2दीर्घ(&ptr, &ks->thपढ़ोid);
		अगर (!ks->thपढ़ोid) अणु
			kgdb_contthपढ़ो = शून्य;
		पूर्ण अन्यथा अणु
			thपढ़ो = getthपढ़ो(ks->linux_regs, ks->thपढ़ोid);
			अगर (!thपढ़ो && ks->thपढ़ोid > 0) अणु
				error_packet(remcom_out_buffer, -EINVAL);
				अवरोध;
			पूर्ण
			kgdb_contthपढ़ो = thपढ़ो;
		पूर्ण
		म_नकल(remcom_out_buffer, "OK");
		अवरोध;
	पूर्ण
पूर्ण

/* Handle the 'T' thपढ़ो query packets */
अटल व्योम gdb_cmd_thपढ़ो(काष्ठा kgdb_state *ks)
अणु
	अक्षर *ptr = &remcom_in_buffer[1];
	काष्ठा task_काष्ठा *thपढ़ो;

	kgdb_hex2दीर्घ(&ptr, &ks->thपढ़ोid);
	thपढ़ो = getthपढ़ो(ks->linux_regs, ks->thपढ़ोid);
	अगर (thपढ़ो)
		म_नकल(remcom_out_buffer, "OK");
	अन्यथा
		error_packet(remcom_out_buffer, -EINVAL);
पूर्ण

/* Handle the 'z' or 'Z' अवरोधpoपूर्णांक हटाओ or set packets */
अटल व्योम gdb_cmd_अवरोध(काष्ठा kgdb_state *ks)
अणु
	/*
	 * Since GDB-5.3, it's been drafted that '0' is a software
	 * अवरोधpoपूर्णांक, '1' is a hardware breakpoint, so let's करो that.
	 */
	अक्षर *bpt_type = &remcom_in_buffer[1];
	अक्षर *ptr = &remcom_in_buffer[2];
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ length;
	पूर्णांक error = 0;

	अगर (arch_kgdb_ops.set_hw_अवरोधpoपूर्णांक && *bpt_type >= '1') अणु
		/* Unsupported */
		अगर (*bpt_type > '4')
			वापस;
	पूर्ण अन्यथा अणु
		अगर (*bpt_type != '0' && *bpt_type != '1')
			/* Unsupported. */
			वापस;
	पूर्ण

	/*
	 * Test अगर this is a hardware अवरोधpoपूर्णांक, and
	 * अगर we support it:
	 */
	अगर (*bpt_type == '1' && !(arch_kgdb_ops.flags & KGDB_HW_BREAKPOINT))
		/* Unsupported. */
		वापस;

	अगर (*(ptr++) != ',') अणु
		error_packet(remcom_out_buffer, -EINVAL);
		वापस;
	पूर्ण
	अगर (!kgdb_hex2दीर्घ(&ptr, &addr)) अणु
		error_packet(remcom_out_buffer, -EINVAL);
		वापस;
	पूर्ण
	अगर (*(ptr++) != ',' ||
		!kgdb_hex2दीर्घ(&ptr, &length)) अणु
		error_packet(remcom_out_buffer, -EINVAL);
		वापस;
	पूर्ण

	अगर (remcom_in_buffer[0] == 'Z' && *bpt_type == '0')
		error = dbg_set_sw_अवरोध(addr);
	अन्यथा अगर (remcom_in_buffer[0] == 'z' && *bpt_type == '0')
		error = dbg_हटाओ_sw_अवरोध(addr);
	अन्यथा अगर (remcom_in_buffer[0] == 'Z')
		error = arch_kgdb_ops.set_hw_अवरोधpoपूर्णांक(addr,
			(पूर्णांक)length, *bpt_type - '0');
	अन्यथा अगर (remcom_in_buffer[0] == 'z')
		error = arch_kgdb_ops.हटाओ_hw_अवरोधpoपूर्णांक(addr,
			(पूर्णांक) length, *bpt_type - '0');

	अगर (error == 0)
		म_नकल(remcom_out_buffer, "OK");
	अन्यथा
		error_packet(remcom_out_buffer, error);
पूर्ण

/* Handle the 'C' संकेत / exception passing packets */
अटल पूर्णांक gdb_cmd_exception_pass(काष्ठा kgdb_state *ks)
अणु
	/* C09 == pass exception
	 * C15 == detach kgdb, pass exception
	 */
	अगर (remcom_in_buffer[1] == '0' && remcom_in_buffer[2] == '9') अणु

		ks->pass_exception = 1;
		remcom_in_buffer[0] = 'c';

	पूर्ण अन्यथा अगर (remcom_in_buffer[1] == '1' && remcom_in_buffer[2] == '5') अणु

		ks->pass_exception = 1;
		remcom_in_buffer[0] = 'D';
		dbg_हटाओ_all_अवरोध();
		kgdb_connected = 0;
		वापस 1;

	पूर्ण अन्यथा अणु
		gdbstub_msg_ग_लिखो("KGDB only knows signal 9 (pass)"
			" and 15 (pass and disconnect)\n"
			"Executing a continue without signal passing\n", 0);
		remcom_in_buffer[0] = 'c';
	पूर्ण

	/* Indicate fall through */
	वापस -1;
पूर्ण

/*
 * This function perक्रमms all gdbserial command processing
 */
पूर्णांक gdb_serial_stub(काष्ठा kgdb_state *ks)
अणु
	पूर्णांक error = 0;
	पूर्णांक पंचांगp;

	/* Initialize comm buffer and globals. */
	स_रखो(remcom_out_buffer, 0, माप(remcom_out_buffer));
	kgdb_usethपढ़ो = kgdb_info[ks->cpu].task;
	ks->kgdb_usethपढ़ोid = shaकरोw_pid(kgdb_info[ks->cpu].task->pid);
	ks->pass_exception = 0;

	अगर (kgdb_connected) अणु
		अचिन्हित अक्षर thref[BUF_THREAD_ID_SIZE];
		अक्षर *ptr;

		/* Reply to host that an exception has occurred */
		ptr = remcom_out_buffer;
		*ptr++ = 'T';
		ptr = hex_byte_pack(ptr, ks->signo);
		ptr += म_माप(म_नकल(ptr, "thread:"));
		पूर्णांक_to_thपढ़ोref(thref, shaकरोw_pid(current->pid));
		ptr = pack_thपढ़ोid(ptr, thref);
		*ptr++ = ';';
		put_packet(remcom_out_buffer);
	पूर्ण

	जबतक (1) अणु
		error = 0;

		/* Clear the out buffer. */
		स_रखो(remcom_out_buffer, 0, माप(remcom_out_buffer));

		get_packet(remcom_in_buffer);

		चयन (remcom_in_buffer[0]) अणु
		हाल '?': /* gdbserial status */
			gdb_cmd_status(ks);
			अवरोध;
		हाल 'g': /* वापस the value of the CPU रेजिस्टरs */
			gdb_cmd_getregs(ks);
			अवरोध;
		हाल 'G': /* set the value of the CPU रेजिस्टरs - वापस OK */
			gdb_cmd_setregs(ks);
			अवरोध;
		हाल 'm': /* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
			gdb_cmd_memपढ़ो(ks);
			अवरोध;
		हाल 'M': /* MAA..AA,LLLL: Write LLLL bytes at address AA..AA */
			gdb_cmd_memग_लिखो(ks);
			अवरोध;
#अगर DBG_MAX_REG_NUM > 0
		हाल 'p': /* pXX Return gdb रेजिस्टर XX (in hex) */
			gdb_cmd_reg_get(ks);
			अवरोध;
		हाल 'P': /* PXX=aaaa Set gdb रेजिस्टर XX to aaaa (in hex) */
			gdb_cmd_reg_set(ks);
			अवरोध;
#पूर्ण_अगर /* DBG_MAX_REG_NUM > 0 */
		हाल 'X': /* XAA..AA,LLLL: Write LLLL bytes at address AA..AA */
			gdb_cmd_binग_लिखो(ks);
			अवरोध;
			/* समाप्त or detach. KGDB should treat this like a
			 * जारी.
			 */
		हाल 'D': /* Debugger detach */
		हाल 'k': /* Debugger detach via समाप्त */
			gdb_cmd_detachसमाप्त(ks);
			जाओ शेष_handle;
		हाल 'R': /* Reboot */
			अगर (gdb_cmd_reboot(ks))
				जाओ शेष_handle;
			अवरोध;
		हाल 'q': /* query command */
			gdb_cmd_query(ks);
			अवरोध;
		हाल 'H': /* task related */
			gdb_cmd_task(ks);
			अवरोध;
		हाल 'T': /* Query thपढ़ो status */
			gdb_cmd_thपढ़ो(ks);
			अवरोध;
		हाल 'z': /* Break poपूर्णांक हटाओ */
		हाल 'Z': /* Break poपूर्णांक set */
			gdb_cmd_अवरोध(ks);
			अवरोध;
#अगर_घोषित CONFIG_KGDB_KDB
		हाल '3': /* Escape पूर्णांकo back पूर्णांकo kdb */
			अगर (remcom_in_buffer[1] == '\0') अणु
				gdb_cmd_detachसमाप्त(ks);
				वापस DBG_PASS_EVENT;
			पूर्ण
#पूर्ण_अगर
			fallthrough;
		हाल 'C': /* Exception passing */
			पंचांगp = gdb_cmd_exception_pass(ks);
			अगर (पंचांगp > 0)
				जाओ शेष_handle;
			अगर (पंचांगp == 0)
				अवरोध;
			fallthrough;	/* on पंचांगp < 0 */
		हाल 'c': /* Continue packet */
		हाल 's': /* Single step packet */
			अगर (kgdb_contthपढ़ो && kgdb_contthपढ़ो != current) अणु
				/* Can't चयन thपढ़ोs in kgdb */
				error_packet(remcom_out_buffer, -EINVAL);
				अवरोध;
			पूर्ण
			fallthrough;	/* to शेष processing */
		शेष:
शेष_handle:
			error = kgdb_arch_handle_exception(ks->ex_vector,
						ks->signo,
						ks->err_code,
						remcom_in_buffer,
						remcom_out_buffer,
						ks->linux_regs);
			/*
			 * Leave cmd processing on error, detach,
			 * समाप्त, जारी, or single step.
			 */
			अगर (error >= 0 || remcom_in_buffer[0] == 'D' ||
			    remcom_in_buffer[0] == 'k') अणु
				error = 0;
				जाओ kgdb_निकास;
			पूर्ण

		पूर्ण

		/* reply to the request */
		put_packet(remcom_out_buffer);
	पूर्ण

kgdb_निकास:
	अगर (ks->pass_exception)
		error = 1;
	वापस error;
पूर्ण

पूर्णांक gdbstub_state(काष्ठा kgdb_state *ks, अक्षर *cmd)
अणु
	पूर्णांक error;

	चयन (cmd[0]) अणु
	हाल 'e':
		error = kgdb_arch_handle_exception(ks->ex_vector,
						   ks->signo,
						   ks->err_code,
						   remcom_in_buffer,
						   remcom_out_buffer,
						   ks->linux_regs);
		वापस error;
	हाल 's':
	हाल 'c':
		strscpy(remcom_in_buffer, cmd, माप(remcom_in_buffer));
		वापस 0;
	हाल '$':
		strscpy(remcom_in_buffer, cmd, माप(remcom_in_buffer));
		gdbstub_use_prev_in_buf = म_माप(remcom_in_buffer);
		gdbstub_prev_in_buf_pos = 0;
		वापस 0;
	पूर्ण
	dbg_io_ops->ग_लिखो_अक्षर('+');
	put_packet(remcom_out_buffer);
	वापस 0;
पूर्ण

/**
 * gdbstub_निकास - Send an निकास message to GDB
 * @status: The निकास code to report.
 */
व्योम gdbstub_निकास(पूर्णांक status)
अणु
	अचिन्हित अक्षर checksum, ch, buffer[3];
	पूर्णांक loop;

	अगर (!kgdb_connected)
		वापस;
	kgdb_connected = 0;

	अगर (!dbg_io_ops || dbg_kdb_mode)
		वापस;

	buffer[0] = 'W';
	buffer[1] = hex_asc_hi(status);
	buffer[2] = hex_asc_lo(status);

	dbg_io_ops->ग_लिखो_अक्षर('$');
	checksum = 0;

	क्रम (loop = 0; loop < 3; loop++) अणु
		ch = buffer[loop];
		checksum += ch;
		dbg_io_ops->ग_लिखो_अक्षर(ch);
	पूर्ण

	dbg_io_ops->ग_लिखो_अक्षर('#');
	dbg_io_ops->ग_लिखो_अक्षर(hex_asc_hi(checksum));
	dbg_io_ops->ग_लिखो_अक्षर(hex_asc_lo(checksum));

	/* make sure the output is flushed, lest the bootloader clobber it */
	अगर (dbg_io_ops->flush)
		dbg_io_ops->flush();
पूर्ण
