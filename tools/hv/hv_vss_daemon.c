<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An implementation of the host initiated guest snapshot क्रम Hyper-V.
 *
 * Copyright (C) 2013, Microsoft, Inc.
 * Author : K. Y. Srinivasan <kys@microsoft.com>
 */


#समावेश <sys/types.h>
#समावेश <sys/poll.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/sysmacros.h>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <mntent.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/major.h>
#समावेश <linux/hyperv.h>
#समावेश <syslog.h>
#समावेश <getopt.h>
#समावेश <stdbool.h>
#समावेश <dirent.h>

अटल bool fs_frozen;

/* Don't use syslog() in the function since that can cause ग_लिखो to disk */
अटल पूर्णांक vss_करो_मुक्तze(अक्षर *dir, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक ret, fd = खोलो(dir, O_RDONLY);

	अगर (fd < 0)
		वापस 1;

	ret = ioctl(fd, cmd, 0);

	/*
	 * If a partition is mounted more than once, only the first
	 * FREEZE/THAW can succeed and the later ones will get
	 * EBUSY/EINVAL respectively: there could be 2 हालs:
	 * 1) a user may mount the same partition to dअगरferent directories
	 *  by mistake or on purpose;
	 * 2) The subvolume of btrfs appears to have the same partition
	 * mounted more than once.
	 */
	अगर (ret) अणु
		अगर ((cmd == FIFREEZE && त्रुटि_सं == EBUSY) ||
		    (cmd == FITHAW && त्रुटि_सं == EINVAL)) अणु
			बंद(fd);
			वापस 0;
		पूर्ण
	पूर्ण

	बंद(fd);
	वापस !!ret;
पूर्ण

अटल bool is_dev_loop(स्थिर अक्षर *blkname)
अणु
	अक्षर *buffer;
	सूची *dir;
	काष्ठा dirent *entry;
	bool ret = false;

	buffer = दो_स्मृति(PATH_MAX);
	अगर (!buffer) अणु
		syslog(LOG_ERR, "Can't allocate memory!");
		निकास(1);
	पूर्ण

	snम_लिखो(buffer, PATH_MAX, "%s/loop", blkname);
	अगर (!access(buffer, R_OK | X_OK)) अणु
		ret = true;
		जाओ मुक्त_buffer;
	पूर्ण अन्यथा अगर (त्रुटि_सं != ENOENT) अणु
		syslog(LOG_ERR, "Can't access: %s; error:%d %s!",
		       buffer, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	snम_लिखो(buffer, PATH_MAX, "%s/slaves", blkname);
	dir = सूची_खोलो(buffer);
	अगर (!dir) अणु
		अगर (त्रुटि_सं != ENOENT)
			syslog(LOG_ERR, "Can't opendir: %s; error:%d %s!",
			       buffer, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		जाओ मुक्त_buffer;
	पूर्ण

	जबतक ((entry = सूची_पढ़ो(dir)) != शून्य) अणु
		अगर (म_भेद(entry->d_name, ".") == 0 ||
		    म_भेद(entry->d_name, "..") == 0)
			जारी;

		snम_लिखो(buffer, PATH_MAX, "%s/slaves/%s", blkname,
			 entry->d_name);
		अगर (is_dev_loop(buffer)) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	बंद_सूची(dir);
मुक्त_buffer:
	मुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक vss_operate(पूर्णांक operation)
अणु
	अक्षर match[] = "/dev/";
	खाता *mounts;
	काष्ठा mntent *ent;
	काष्ठा stat sb;
	अक्षर errdir[1024] = अणु0पूर्ण;
	अक्षर blkdir[23]; /* /sys/dev/block/XXX:XXX */
	अचिन्हित पूर्णांक cmd;
	पूर्णांक error = 0, root_seen = 0, save_त्रुटि_सं = 0;

	चयन (operation) अणु
	हाल VSS_OP_FREEZE:
		cmd = FIFREEZE;
		अवरोध;
	हाल VSS_OP_THAW:
		cmd = FITHAW;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	mounts = seपंचांगntent("/proc/mounts", "r");
	अगर (mounts == शून्य)
		वापस -1;

	जबतक ((ent = geपंचांगntent(mounts))) अणु
		अगर (म_भेदन(ent->mnt_fsname, match, म_माप(match)))
			जारी;
		अगर (stat(ent->mnt_fsname, &sb)) अणु
			syslog(LOG_ERR, "Can't stat: %s; error:%d %s!",
			       ent->mnt_fsname, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पूर्ण अन्यथा अणु
			प्र_लिखो(blkdir, "/sys/dev/block/%d:%d",
				major(sb.st_rdev), minor(sb.st_rdev));
			अगर (is_dev_loop(blkdir))
				जारी;
		पूर्ण
		अगर (hयंत्रntopt(ent, MNTOPT_RO) != शून्य)
			जारी;
		अगर (म_भेद(ent->mnt_type, "vfat") == 0)
			जारी;
		अगर (म_भेद(ent->mnt_dir, "/") == 0) अणु
			root_seen = 1;
			जारी;
		पूर्ण
		error |= vss_करो_मुक्तze(ent->mnt_dir, cmd);
		अगर (operation == VSS_OP_FREEZE) अणु
			अगर (error)
				जाओ err;
			fs_frozen = true;
		पूर्ण
	पूर्ण

	endmntent(mounts);

	अगर (root_seen) अणु
		error |= vss_करो_मुक्तze("/", cmd);
		अगर (operation == VSS_OP_FREEZE) अणु
			अगर (error)
				जाओ err;
			fs_frozen = true;
		पूर्ण
	पूर्ण

	अगर (operation == VSS_OP_THAW && !error)
		fs_frozen = false;

	जाओ out;
err:
	save_त्रुटि_सं = त्रुटि_सं;
	अगर (ent) अणु
		म_नकलन(errdir, ent->mnt_dir, माप(errdir)-1);
		endmntent(mounts);
	पूर्ण
	vss_operate(VSS_OP_THAW);
	fs_frozen = false;
	/* Call syslog after we thaw all fileप्रणालीs */
	अगर (ent)
		syslog(LOG_ERR, "FREEZE of %s failed; error:%d %s",
		       errdir, save_त्रुटि_सं, म_त्रुटि(save_त्रुटि_सं));
	अन्यथा
		syslog(LOG_ERR, "FREEZE of / failed; error:%d %s", save_त्रुटि_सं,
		       म_त्रुटि(save_त्रुटि_सं));
out:
	वापस error;
पूर्ण

व्योम prपूर्णांक_usage(अक्षर *argv[])
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: %s [options]\n"
		"Options are:\n"
		"  -n, --no-daemon        stay in foreground, don't daemonize\n"
		"  -h, --help             print this help\n", argv[0]);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक vss_fd = -1, len;
	पूर्णांक error;
	काष्ठा pollfd pfd;
	पूर्णांक	op;
	काष्ठा hv_vss_msg vss_msg[1];
	पूर्णांक daemonize = 1, दीर्घ_index = 0, opt;
	पूर्णांक in_handshake;
	__u32 kernel_modver;

	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु"help",	no_argument,	   0,  'h' पूर्ण,
		अणु"no-daemon",	no_argument,	   0,  'n' पूर्ण,
		अणु0,		0,		   0,  0   पूर्ण
	पूर्ण;

	जबतक ((opt = getopt_दीर्घ(argc, argv, "hn", दीर्घ_options,
				  &दीर्घ_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'n':
			daemonize = 0;
			अवरोध;
		हाल 'h':
			prपूर्णांक_usage(argv);
			निकास(0);
		शेष:
			prपूर्णांक_usage(argv);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	अगर (daemonize && daemon(1, 0))
		वापस 1;

	खोलोlog("Hyper-V VSS", 0, LOG_USER);
	syslog(LOG_INFO, "VSS starting; pid is:%d", getpid());

reखोलो_vss_fd:
	अगर (vss_fd != -1)
		बंद(vss_fd);
	अगर (fs_frozen) अणु
		अगर (vss_operate(VSS_OP_THAW) || fs_frozen) अणु
			syslog(LOG_ERR, "failed to thaw file system: err=%d",
			       त्रुटि_सं);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	in_handshake = 1;
	vss_fd = खोलो("/dev/vmbus/hv_vss", O_RDWR);
	अगर (vss_fd < 0) अणु
		syslog(LOG_ERR, "open /dev/vmbus/hv_vss failed; error: %d %s",
		       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
	/*
	 * Register ourselves with the kernel.
	 */
	vss_msg->vss_hdr.operation = VSS_OP_REGISTER1;

	len = ग_लिखो(vss_fd, vss_msg, माप(काष्ठा hv_vss_msg));
	अगर (len < 0) अणु
		syslog(LOG_ERR, "registration to kernel failed; error: %d %s",
		       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		बंद(vss_fd);
		निकास(निकास_त्रुटि);
	पूर्ण

	pfd.fd = vss_fd;

	जबतक (1) अणु
		pfd.events = POLLIN;
		pfd.revents = 0;

		अगर (poll(&pfd, 1, -1) < 0) अणु
			syslog(LOG_ERR, "poll failed; error:%d %s", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			अगर (त्रुटि_सं == EINVAL) अणु
				बंद(vss_fd);
				निकास(निकास_त्रुटि);
			पूर्ण
			अन्यथा
				जारी;
		पूर्ण

		len = पढ़ो(vss_fd, vss_msg, माप(काष्ठा hv_vss_msg));

		अगर (in_handshake) अणु
			अगर (len != माप(kernel_modver)) अणु
				syslog(LOG_ERR, "invalid version negotiation");
				निकास(निकास_त्रुटि);
			पूर्ण
			kernel_modver = *(__u32 *)vss_msg;
			in_handshake = 0;
			syslog(LOG_INFO, "VSS: kernel module version: %d",
			       kernel_modver);
			जारी;
		पूर्ण

		अगर (len != माप(काष्ठा hv_vss_msg)) अणु
			syslog(LOG_ERR, "read failed; error:%d %s",
			       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_vss_fd;
		पूर्ण

		op = vss_msg->vss_hdr.operation;
		error =  HV_S_OK;

		चयन (op) अणु
		हाल VSS_OP_FREEZE:
		हाल VSS_OP_THAW:
			error = vss_operate(op);
			syslog(LOG_INFO, "VSS: op=%s: %s\n",
				op == VSS_OP_FREEZE ? "FREEZE" : "THAW",
				error ? "failed" : "succeeded");

			अगर (error) अणु
				error = HV_E_FAIL;
				syslog(LOG_ERR, "op=%d failed!", op);
				syslog(LOG_ERR, "report it with these files:");
				syslog(LOG_ERR, "/etc/fstab and /proc/mounts");
			पूर्ण
			अवरोध;
		हाल VSS_OP_HOT_BACKUP:
			syslog(LOG_INFO, "VSS: op=CHECK HOT BACKUP\n");
			अवरोध;
		शेष:
			syslog(LOG_ERR, "Illegal op:%d\n", op);
		पूर्ण

		/*
		 * The ग_लिखो() may वापस an error due to the faked VSS_OP_THAW
		 * message upon hibernation. Ignore the error by resetting the
		 * dev file, i.e. closing and re-खोलोing it.
		 */
		vss_msg->error = error;
		len = ग_लिखो(vss_fd, vss_msg, माप(काष्ठा hv_vss_msg));
		अगर (len != माप(काष्ठा hv_vss_msg)) अणु
			syslog(LOG_ERR, "write failed; error: %d %s", त्रुटि_सं,
			       म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_vss_fd;
		पूर्ण
	पूर्ण

	बंद(vss_fd);
	निकास(0);
पूर्ण
