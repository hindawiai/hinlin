<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1995, 1996  Gero Kuhlmann <gero@gkminix.han.de>
 *
 *  Allow an NFS fileप्रणाली to be mounted as root. The way this works is:
 *     (1) Use the IP स्वतःconfig mechanism to set local IP addresses and routes.
 *     (2) Conकाष्ठा the device string and the options string using DHCP
 *         option 17 and/or kernel command line options.
 *     (3) When mount_root() sets up the root file प्रणाली, pass these strings
 *         to the NFS client's regular mount पूर्णांकerface via sys_mount().
 *
 *
 *	Changes:
 *
 *	Alan Cox	:	Removed get_address name clash with FPU.
 *	Alan Cox	:	Reक्रमmatted a bit.
 *	Gero Kuhlmann	:	Code cleanup
 *	Michael Rausch  :	Fixed recognition of an incoming RARP answer.
 *	Martin Mares	: (2.0)	Auto-configuration via BOOTP supported.
 *	Martin Mares	:	Manual selection of पूर्णांकerface & BOOTP/RARP.
 *	Martin Mares	:	Using network routes instead of host routes,
 *				allowing the शेष configuration to be used
 *				क्रम normal operation of the host.
 *	Martin Mares	:	Ranकरोmized समयr with exponential backoff
 *				installed to minimize network congestion.
 *	Martin Mares	:	Code cleanup.
 *	Martin Mares	: (2.1)	BOOTP and RARP made configuration options.
 *	Martin Mares	:	Server hostname generation fixed.
 *	Gerd Knorr	:	Fixed wired inode handling
 *	Martin Mares	: (2.2)	"0.0.0.0" addresses from command line ignored.
 *	Martin Mares	:	RARP replies not tested क्रम server address.
 *	Gero Kuhlmann	: (2.3) Some bug fixes and code cleanup again (please
 *				send me your new patches _beक्रमe_ bothering
 *				Linus so that I करोn' always have to cleanup
 *				_afterwards_ - thanks)
 *	Gero Kuhlmann	:	Last changes of Martin Mares unकरोne.
 *	Gero Kuhlmann	: 	RARP replies are tested क्रम specअगरied server
 *				again. However, it's now possible to have
 *				dअगरferent RARP and NFS servers.
 *	Gero Kuhlmann	:	"0.0.0.0" addresses from command line are
 *				now mapped to INADDR_NONE.
 *	Gero Kuhlmann	:	Fixed a bug which prevented BOOTP path name
 *				from being used (thanks to Leo Spiekman)
 *	Andy Walker	:	Allow to specअगरy the NFS server in nfs_root
 *				without giving a path name
 *	Swen Thथञmmler	:	Allow to specअगरy the NFS options in nfs_root
 *				without giving a path name. Fix BOOTP request
 *				क्रम करोमुख्यname (करोमुख्यname is NIS करोमुख्य, not
 *				DNS करोमुख्य!). Skip dummy devices क्रम BOOTP.
 *	Jacek Zapala	:	Fixed a bug which prevented server-ip address
 *				from nfsroot parameter from being used.
 *	Olaf Kirch	:	Adapted to new NFS code.
 *	Jakub Jelinek	:	Free used code segment.
 *	Marko Kohtala	:	Fixed some bugs.
 *	Martin Mares	:	Debug message cleanup
 *	Martin Mares	:	Changed to use the new generic IP layer स्वतःconfig
 *				code. BOOTP and RARP moved there.
 *	Martin Mares	:	Default path now contains host name instead of
 *				host IP address (but host name शेषs to IP
 *				address anyway).
 *	Martin Mares	:	Use root_server_addr appropriately during setup.
 *	Martin Mares	:	Rewrote parameter parsing, now hopefully giving
 *				correct overriding.
 *	Trond Myklebust :	Add in preliminary support क्रम NFSv3 and TCP.
 *				Fix bug in root_nfs_addr(). nfs_data.namlen
 *				is NOT क्रम the length of the hostname.
 *	Hua Qin		:	Support क्रम mounting root file प्रणाली via
 *				NFS over TCP.
 *	Fabian Frederick:	Option parser rebuilt (using parser lib)
 *	Chuck Lever	:	Use super.c's text-based mount option parsing
 *	Chuck Lever	:	Add "nfsrootdebug".
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/utsname.h>
#समावेश <linux/root_dev.h>
#समावेश <net/ipconfig.h>

#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY NFSDBG_ROOT

/* Default path we try to mount. "%s" माला_लो replaced by our IP address */
#घोषणा NFS_ROOT		"/tftpboot/%s"

/* Default NFSROOT mount options. */
#अगर defined(CONFIG_NFS_V2)
#घोषणा NFS_DEF_OPTIONS		"vers=2,tcp,rsize=4096,wsize=4096"
#या_अगर defined(CONFIG_NFS_V3)
#घोषणा NFS_DEF_OPTIONS		"vers=3,tcp,rsize=4096,wsize=4096"
#अन्यथा
#घोषणा NFS_DEF_OPTIONS		"vers=4,tcp,rsize=4096,wsize=4096"
#पूर्ण_अगर

/* Parameters passed from the kernel command line */
अटल अक्षर nfs_root_parms[NFS_MAXPATHLEN + 1] __initdata = "";

/* Text-based mount options passed to super.c */
अटल अक्षर nfs_root_options[256] __initdata = NFS_DEF_OPTIONS;

/* Address of NFS server */
अटल __be32 servaddr __initdata = htonl(INADDR_NONE);

/* Name of directory to mount */
अटल अक्षर nfs_export_path[NFS_MAXPATHLEN + 1] __initdata = "";

/* server:export path string passed to super.c */
अटल अक्षर nfs_root_device[NFS_MAXPATHLEN + 1] __initdata = "";

#अगर_घोषित NFS_DEBUG
/*
 * When the "nfsrootdebug" kernel command line option is specअगरied,
 * enable debugging messages क्रम NFSROOT.
 */
अटल पूर्णांक __init nfs_root_debug(अक्षर *__unused)
अणु
	nfs_debug |= NFSDBG_ROOT | NFSDBG_MOUNT;
	वापस 1;
पूर्ण

__setup("nfsrootdebug", nfs_root_debug);
#पूर्ण_अगर

/*
 *  Parse NFS server and directory inक्रमmation passed on the kernel
 *  command line.
 *
 *  nfsroot=[<server-ip>:]<root-dir>[,<nfs-options>]
 *
 *  If there is a "%s" token in the <root-dir> string, it is replaced
 *  by the ASCII-representation of the client's IP address.
 */
अटल पूर्णांक __init nfs_root_setup(अक्षर *line)
अणु
	ROOT_DEV = Root_NFS;

	अगर (line[0] == '/' || line[0] == ',' || (line[0] >= '0' && line[0] <= '9')) अणु
		strlcpy(nfs_root_parms, line, माप(nfs_root_parms));
	पूर्ण अन्यथा अणु
		माप_प्रकार n = म_माप(line) + माप(NFS_ROOT) - 1;
		अगर (n >= माप(nfs_root_parms))
			line[माप(nfs_root_parms) - माप(NFS_ROOT) - 2] = '\0';
		प्र_लिखो(nfs_root_parms, NFS_ROOT, line);
	पूर्ण

	/*
	 * Extract the IP address of the NFS server containing our
	 * root file प्रणाली, अगर one was specअगरied.
	 *
	 * Note: root_nfs_parse_addr() हटाओs the server-ip from
	 *	 nfs_root_parms, अगर it exists.
	 */
	root_server_addr = root_nfs_parse_addr(nfs_root_parms);

	वापस 1;
पूर्ण

__setup("nfsroot=", nfs_root_setup);

अटल पूर्णांक __init root_nfs_copy(अक्षर *dest, स्थिर अक्षर *src,
				     स्थिर माप_प्रकार destlen)
अणु
	अगर (strlcpy(dest, src, destlen) > destlen)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init root_nfs_cat(अक्षर *dest, स्थिर अक्षर *src,
			       स्थिर माप_प्रकार destlen)
अणु
	माप_प्रकार len = म_माप(dest);

	अगर (len && dest[len - 1] != ',')
		अगर (strlcat(dest, ",", destlen) > destlen)
			वापस -1;

	अगर (strlcat(dest, src, destlen) > destlen)
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Parse out root export path and mount options from
 * passed-in string @incoming.
 *
 * Copy the export path पूर्णांकo @exppath.
 */
अटल पूर्णांक __init root_nfs_parse_options(अक्षर *incoming, अक्षर *exppath,
					 स्थिर माप_प्रकार exppathlen)
अणु
	अक्षर *p;

	/*
	 * Set the NFS remote path
	 */
	p = strsep(&incoming, ",");
	अगर (*p != '\0' && म_भेद(p, "default") != 0)
		अगर (root_nfs_copy(exppath, p, exppathlen))
			वापस -1;

	/*
	 * @incoming now poपूर्णांकs to the rest of the string; अगर it
	 * contains something, append it to our root options buffer
	 */
	अगर (incoming != शून्य && *incoming != '\0')
		अगर (root_nfs_cat(nfs_root_options, incoming,
						माप(nfs_root_options)))
			वापस -1;
	वापस 0;
पूर्ण

/*
 *  Decode the export directory path name and NFS options from
 *  the kernel command line.  This has to be करोne late in order to
 *  use a dynamically acquired client IP address क्रम the remote
 *  root directory path.
 *
 *  Returns zero अगर successful; otherwise -1 is वापसed.
 */
अटल पूर्णांक __init root_nfs_data(अक्षर *cmdline)
अणु
	अक्षर mand_options[माप("nolock,addr=") + INET_ADDRSTRLEN + 1];
	पूर्णांक len, retval = -1;
	अक्षर *पंचांगp = शून्य;
	स्थिर माप_प्रकार पंचांगplen = माप(nfs_export_path);

	पंचांगp = kzalloc(पंचांगplen, GFP_KERNEL);
	अगर (पंचांगp == शून्य)
		जाओ out_nomem;
	म_नकल(पंचांगp, NFS_ROOT);

	अगर (root_server_path[0] != '\0') अणु
		dprपूर्णांकk("Root-NFS: DHCPv4 option 17: %s\n",
			root_server_path);
		अगर (root_nfs_parse_options(root_server_path, पंचांगp, पंचांगplen))
			जाओ out_optionstooदीर्घ;
	पूर्ण

	अगर (cmdline[0] != '\0') अणु
		dprपूर्णांकk("Root-NFS: nfsroot=%s\n", cmdline);
		अगर (root_nfs_parse_options(cmdline, पंचांगp, पंचांगplen))
			जाओ out_optionstooदीर्घ;
	पूर्ण

	/*
	 * Append mandatory options क्रम nfsroot so they override
	 * what has come beक्रमe
	 */
	snम_लिखो(mand_options, माप(mand_options), "nolock,addr=%pI4",
			&servaddr);
	अगर (root_nfs_cat(nfs_root_options, mand_options,
						माप(nfs_root_options)))
		जाओ out_optionstooदीर्घ;

	/*
	 * Set up nfs_root_device.  For NFS mounts, this looks like
	 *
	 *	server:/path
	 *
	 * At this poपूर्णांक, utsname()->nodename contains our local
	 * IP address or hostname, set by ipconfig.  If "%s" exists
	 * in पंचांगp, substitute the nodename, then shovel the whole
	 * mess पूर्णांकo nfs_root_device.
	 */
	len = snम_लिखो(nfs_export_path, माप(nfs_export_path),
				पंचांगp, utsname()->nodename);
	अगर (len >= (पूर्णांक)माप(nfs_export_path))
		जाओ out_devnametooदीर्घ;
	len = snम_लिखो(nfs_root_device, माप(nfs_root_device),
				"%pI4:%s", &servaddr, nfs_export_path);
	अगर (len >= (पूर्णांक)माप(nfs_root_device))
		जाओ out_devnametooदीर्घ;

	retval = 0;

out:
	kमुक्त(पंचांगp);
	वापस retval;
out_nomem:
	prपूर्णांकk(KERN_ERR "Root-NFS: could not allocate memory\n");
	जाओ out;
out_optionstooदीर्घ:
	prपूर्णांकk(KERN_ERR "Root-NFS: mount options string too long\n");
	जाओ out;
out_devnametooदीर्घ:
	prपूर्णांकk(KERN_ERR "Root-NFS: root device name too long.\n");
	जाओ out;
पूर्ण

/**
 * nfs_root_data - Return prepared 'data' क्रम NFSROOT mount
 * @root_device: OUT: address of string containing NFSROOT device
 * @root_data: OUT: address of string containing NFSROOT mount options
 *
 * Returns zero and sets @root_device and @root_data अगर successful,
 * otherwise -1 is वापसed.
 */
पूर्णांक __init nfs_root_data(अक्षर **root_device, अक्षर **root_data)
अणु
	servaddr = root_server_addr;
	अगर (servaddr == htonl(INADDR_NONE)) अणु
		prपूर्णांकk(KERN_ERR "Root-NFS: no NFS server address\n");
		वापस -1;
	पूर्ण

	अगर (root_nfs_data(nfs_root_parms) < 0)
		वापस -1;

	*root_device = nfs_root_device;
	*root_data = nfs_root_options;
	वापस 0;
पूर्ण
