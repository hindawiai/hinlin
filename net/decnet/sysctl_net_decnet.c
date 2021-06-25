<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet sysctl support functions
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *
 *
 * Changes:
 * Steve Whitehouse - C99 changes and शेष device handling
 * Steve Whitehouse - Memory buffer settings, like the tcp ones
 *
 */
#समावेश <linux/mm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>

#समावेश <linux/uaccess.h>

#समावेश <net/dn.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>


पूर्णांक decnet_debug_level;
पूर्णांक decnet_समय_रुको = 30;
पूर्णांक decnet_dn_count = 1;
पूर्णांक decnet_di_count = 3;
पूर्णांक decnet_dr_count = 3;
पूर्णांक decnet_log_martians = 1;
पूर्णांक decnet_no_fc_max_cwnd = NSP_MIN_WINDOW;

/* Reasonable शेषs, I hope, based on tcp's शेषs */
दीर्घ sysctl_decnet_mem[3] = अणु 768 << 3, 1024 << 3, 1536 << 3 पूर्ण;
पूर्णांक sysctl_decnet_wmem[3] = अणु 4 * 1024, 16 * 1024, 128 * 1024 पूर्ण;
पूर्णांक sysctl_decnet_rmem[3] = अणु 4 * 1024, 87380, 87380 * 2 पूर्ण;

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक decnet_dst_gc_पूर्णांकerval;
अटल पूर्णांक min_decnet_समय_रुको[] = अणु 5 पूर्ण;
अटल पूर्णांक max_decnet_समय_रुको[] = अणु 600 पूर्ण;
अटल पूर्णांक min_state_count[] = अणु 1 पूर्ण;
अटल पूर्णांक max_state_count[] = अणु NSP_MAXRXTSHIFT पूर्ण;
अटल पूर्णांक min_decnet_dst_gc_पूर्णांकerval[] = अणु 1 पूर्ण;
अटल पूर्णांक max_decnet_dst_gc_पूर्णांकerval[] = अणु 60 पूर्ण;
अटल पूर्णांक min_decnet_no_fc_max_cwnd[] = अणु NSP_MIN_WINDOW पूर्ण;
अटल पूर्णांक max_decnet_no_fc_max_cwnd[] = अणु NSP_MAX_WINDOW पूर्ण;
अटल अक्षर node_name[7] = "???";

अटल काष्ठा ctl_table_header *dn_table_header = शून्य;

/*
 * प्रकार.स :-)
 */
#घोषणा ISNUM(x) (((x) >= '0') && ((x) <= '9'))
#घोषणा ISLOWER(x) (((x) >= 'a') && ((x) <= 'z'))
#घोषणा ISUPPER(x) (((x) >= 'A') && ((x) <= 'Z'))
#घोषणा ISALPHA(x) (ISLOWER(x) || ISUPPER(x))
#घोषणा INVALID_END_CHAR(x) (ISNUM(x) || ISALPHA(x))

अटल व्योम strip_it(अक्षर *str)
अणु
	क्रम(;;) अणु
		चयन (*str) अणु
		हाल ' ':
		हाल '\n':
		हाल '\r':
		हाल ':':
			*str = 0;
			fallthrough;
		हाल 0:
			वापस;
		पूर्ण
		str++;
	पूर्ण
पूर्ण

/*
 * Simple routine to parse an ascii DECnet address
 * पूर्णांकo a network order address.
 */
अटल पूर्णांक parse_addr(__le16 *addr, अक्षर *str)
अणु
	__u16 area, node;

	जबतक(*str && !ISNUM(*str)) str++;

	अगर (*str == 0)
		वापस -1;

	area = (*str++ - '0');
	अगर (ISNUM(*str)) अणु
		area *= 10;
		area += (*str++ - '0');
	पूर्ण

	अगर (*str++ != '.')
		वापस -1;

	अगर (!ISNUM(*str))
		वापस -1;

	node = *str++ - '0';
	अगर (ISNUM(*str)) अणु
		node *= 10;
		node += (*str++ - '0');
	पूर्ण
	अगर (ISNUM(*str)) अणु
		node *= 10;
		node += (*str++ - '0');
	पूर्ण
	अगर (ISNUM(*str)) अणु
		node *= 10;
		node += (*str++ - '0');
	पूर्ण

	अगर ((node > 1023) || (area > 63))
		वापस -1;

	अगर (INVALID_END_CHAR(*str))
		वापस -1;

	*addr = cpu_to_le16((area << 10) | node);

	वापस 0;
पूर्ण

अटल पूर्णांक dn_node_address_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर addr[DN_ASCBUF_LEN];
	माप_प्रकार len;
	__le16 dnaddr;

	अगर (!*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) अणु
		len = (*lenp < DN_ASCBUF_LEN) ? *lenp : (DN_ASCBUF_LEN-1);
		स_नकल(addr, buffer, len);
		addr[len] = 0;
		strip_it(addr);

		अगर (parse_addr(&dnaddr, addr))
			वापस -EINVAL;

		dn_dev_devices_off();

		decnet_address = dnaddr;

		dn_dev_devices_on();

		*ppos += len;

		वापस 0;
	पूर्ण

	dn_addr2asc(le16_to_cpu(decnet_address), addr);
	len = म_माप(addr);
	addr[len++] = '\n';

	अगर (len > *lenp)
		len = *lenp;
	स_नकल(buffer, addr, len);
	*lenp = len;
	*ppos += len;

	वापस 0;
पूर्ण

अटल पूर्णांक dn_def_dev_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	माप_प्रकार len;
	काष्ठा net_device *dev;
	अक्षर devname[17];

	अगर (!*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (*lenp > 16)
			वापस -E2BIG;

		स_नकल(devname, buffer, *lenp);
		devname[*lenp] = 0;
		strip_it(devname);

		dev = dev_get_by_name(&init_net, devname);
		अगर (dev == शून्य)
			वापस -ENODEV;

		अगर (dev->dn_ptr == शून्य) अणु
			dev_put(dev);
			वापस -ENODEV;
		पूर्ण

		अगर (dn_dev_set_शेष(dev, 1)) अणु
			dev_put(dev);
			वापस -ENODEV;
		पूर्ण
		*ppos += *lenp;

		वापस 0;
	पूर्ण

	dev = dn_dev_get_शेष();
	अगर (dev == शून्य) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	म_नकल(devname, dev->name);
	dev_put(dev);
	len = म_माप(devname);
	devname[len++] = '\n';

	अगर (len > *lenp) len = *lenp;

	स_नकल(buffer, devname, len);
	*lenp = len;
	*ppos += len;

	वापस 0;
पूर्ण

अटल काष्ठा ctl_table dn_table[] = अणु
	अणु
		.procname = "node_address",
		.maxlen = 7,
		.mode = 0644,
		.proc_handler = dn_node_address_handler,
	पूर्ण,
	अणु
		.procname = "node_name",
		.data = node_name,
		.maxlen = 7,
		.mode = 0644,
		.proc_handler = proc_करोstring,
	पूर्ण,
	अणु
		.procname = "default_device",
		.maxlen = 16,
		.mode = 0644,
		.proc_handler = dn_def_dev_handler,
	पूर्ण,
	अणु
		.procname = "time_wait",
		.data = &decnet_समय_रुको,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_decnet_समय_रुको,
		.extra2 = &max_decnet_समय_रुको
	पूर्ण,
	अणु
		.procname = "dn_count",
		.data = &decnet_dn_count,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_state_count,
		.extra2 = &max_state_count
	पूर्ण,
	अणु
		.procname = "di_count",
		.data = &decnet_di_count,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_state_count,
		.extra2 = &max_state_count
	पूर्ण,
	अणु
		.procname = "dr_count",
		.data = &decnet_dr_count,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_state_count,
		.extra2 = &max_state_count
	पूर्ण,
	अणु
		.procname = "dst_gc_interval",
		.data = &decnet_dst_gc_पूर्णांकerval,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_decnet_dst_gc_पूर्णांकerval,
		.extra2 = &max_decnet_dst_gc_पूर्णांकerval
	पूर्ण,
	अणु
		.procname = "no_fc_max_cwnd",
		.data = &decnet_no_fc_max_cwnd,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_decnet_no_fc_max_cwnd,
		.extra2 = &max_decnet_no_fc_max_cwnd
	पूर्ण,
       अणु
		.procname = "decnet_mem",
		.data = &sysctl_decnet_mem,
		.maxlen = माप(sysctl_decnet_mem),
		.mode = 0644,
		.proc_handler = proc_करोuदीर्घvec_minmax
	पूर्ण,
	अणु
		.procname = "decnet_rmem",
		.data = &sysctl_decnet_rmem,
		.maxlen = माप(sysctl_decnet_rmem),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname = "decnet_wmem",
		.data = &sysctl_decnet_wmem,
		.maxlen = माप(sysctl_decnet_wmem),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname = "debug",
		.data = &decnet_debug_level,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम dn_रेजिस्टर_sysctl(व्योम)
अणु
	dn_table_header = रेजिस्टर_net_sysctl(&init_net, "net/decnet", dn_table);
पूर्ण

व्योम dn_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(dn_table_header);
पूर्ण

#अन्यथा  /* CONFIG_SYSCTL */
व्योम dn_unरेजिस्टर_sysctl(व्योम)
अणु
पूर्ण
व्योम dn_रेजिस्टर_sysctl(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
