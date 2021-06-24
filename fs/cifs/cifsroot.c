<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMB root file प्रणाली support
 *
 * Copyright (c) 2019 Paulo Alcantara <palcantara@suse.de>
 */
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/root_dev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <net/ipconfig.h>

#घोषणा DEFAULT_MNT_OPTS \
	"vers=1.0,cifsacl,mfsymlinks,rsize=1048576,wsize=65536,uid=0,gid=0," \
	"hard,rootfs"

अटल अक्षर root_dev[2048] __initdata = "";
अटल अक्षर root_opts[1024] __initdata = DEFAULT_MNT_OPTS;

अटल __be32 __init parse_srvaddr(अक्षर *start, अक्षर *end)
अणु
	/* TODO: ipv6 support */
	अक्षर addr[माप("aaa.bbb.ccc.ddd")];
	पूर्णांक i = 0;

	जबतक (start < end && i < माप(addr) - 1) अणु
		अगर (है_अंक(*start) || *start == '.')
			addr[i++] = *start;
		start++;
	पूर्ण
	addr[i] = '\0';
	वापस in_aton(addr);
पूर्ण

/* cअगरsroot=//<server-ip>/<share>[,options] */
अटल पूर्णांक __init cअगरs_root_setup(अक्षर *line)
अणु
	अक्षर *s;
	पूर्णांक len;
	__be32 srvaddr = htonl(INADDR_NONE);

	ROOT_DEV = Root_CIFS;

	अगर (म_माप(line) > 3 && line[0] == '/' && line[1] == '/') अणु
		s = म_अक्षर(&line[2], '/');
		अगर (!s || s[1] == '\0')
			वापस 1;

		/* make s poपूर्णांक to ',' or '\0' at end of line */
		s = म_अक्षरnul(s, ',');
		/* len is म_माप(unc) + '\0' */
		len = s - line + 1;
		अगर (len > माप(root_dev)) अणु
			pr_err("Root-CIFS: UNC path too long\n");
			वापस 1;
		पूर्ण
		strlcpy(root_dev, line, len);
		srvaddr = parse_srvaddr(&line[2], s);
		अगर (*s) अणु
			पूर्णांक n = snम_लिखो(root_opts,
					 माप(root_opts), "%s,%s",
					 DEFAULT_MNT_OPTS, s + 1);
			अगर (n >= माप(root_opts)) अणु
				pr_err("Root-CIFS: mount options string too long\n");
				root_opts[माप(root_opts)-1] = '\0';
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	root_server_addr = srvaddr;

	वापस 1;
पूर्ण

__setup("cifsroot=", cअगरs_root_setup);

पूर्णांक __init cअगरs_root_data(अक्षर **dev, अक्षर **opts)
अणु
	अगर (!root_dev[0] || root_server_addr == htonl(INADDR_NONE)) अणु
		pr_err("Root-CIFS: no SMB server address\n");
		वापस -1;
	पूर्ण

	*dev = root_dev;
	*opts = root_opts;

	वापस 0;
पूर्ण
