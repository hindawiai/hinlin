<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An implementation of host to guest copy functionality क्रम Linux.
 *
 * Copyright (C) 2014, Microsoft, Inc.
 *
 * Author : K. Y. Srinivasan <kys@microsoft.com>
 */


#समावेश <sys/types.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/hyperv.h>
#समावेश <linux/सीमा.स>
#समावेश <syslog.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <getopt.h>

अटल पूर्णांक target_fd;
अटल अक्षर target_fname[PATH_MAX];
अटल अचिन्हित दीर्घ दीर्घ filesize;

अटल पूर्णांक hv_start_fcopy(काष्ठा hv_start_fcopy *smsg)
अणु
	पूर्णांक error = HV_E_FAIL;
	अक्षर *q, *p;

	filesize = 0;
	p = (अक्षर *)smsg->path_name;
	snम_लिखो(target_fname, माप(target_fname), "%s/%s",
		 (अक्षर *)smsg->path_name, (अक्षर *)smsg->file_name);

	syslog(LOG_INFO, "Target file name: %s", target_fname);
	/*
	 * Check to see अगर the path is alपढ़ोy in place; अगर not,
	 * create अगर required.
	 */
	जबतक ((q = म_अक्षर(p, '/')) != शून्य) अणु
		अगर (q == p) अणु
			p++;
			जारी;
		पूर्ण
		*q = '\0';
		अगर (access((अक्षर *)smsg->path_name, F_OK)) अणु
			अगर (smsg->copy_flags & CREATE_PATH) अणु
				अगर (सूची_गढ़ो((अक्षर *)smsg->path_name, 0755)) अणु
					syslog(LOG_ERR, "Failed to create %s",
						(अक्षर *)smsg->path_name);
					जाओ करोne;
				पूर्ण
			पूर्ण अन्यथा अणु
				syslog(LOG_ERR, "Invalid path: %s",
					(अक्षर *)smsg->path_name);
				जाओ करोne;
			पूर्ण
		पूर्ण
		p = q + 1;
		*q = '/';
	पूर्ण

	अगर (!access(target_fname, F_OK)) अणु
		syslog(LOG_INFO, "File: %s exists", target_fname);
		अगर (!(smsg->copy_flags & OVER_WRITE)) अणु
			error = HV_ERROR_ALREADY_EXISTS;
			जाओ करोne;
		पूर्ण
	पूर्ण

	target_fd = खोलो(target_fname,
			 O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0744);
	अगर (target_fd == -1) अणु
		syslog(LOG_INFO, "Open Failed: %s", म_त्रुटि(त्रुटि_सं));
		जाओ करोne;
	पूर्ण

	error = 0;
करोne:
	अगर (error)
		target_fname[0] = '\0';
	वापस error;
पूर्ण

अटल पूर्णांक hv_copy_data(काष्ठा hv_करो_fcopy *cpmsg)
अणु
	sमाप_प्रकार bytes_written;
	पूर्णांक ret = 0;

	bytes_written = pग_लिखो(target_fd, cpmsg->data, cpmsg->size,
				cpmsg->offset);

	filesize += cpmsg->size;
	अगर (bytes_written != cpmsg->size) अणु
		चयन (त्रुटि_सं) अणु
		हाल ENOSPC:
			ret = HV_ERROR_DISK_FULL;
			अवरोध;
		शेष:
			ret = HV_E_FAIL;
			अवरोध;
		पूर्ण
		syslog(LOG_ERR, "pwrite failed to write %llu bytes: %ld (%s)",
		       filesize, (दीर्घ)bytes_written, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Reset target_fname to "" in the two below functions क्रम hibernation: अगर
 * the fcopy operation is पातed by hibernation, the daemon should हटाओ the
 * partially-copied file; to achieve this, the hv_utils driver always fakes a
 * CANCEL_FCOPY message upon suspend, and later when the VM resumes back,
 * the daemon calls hv_copy_cancel() to हटाओ the file; अगर a file is copied
 * successfully beक्रमe suspend, hv_copy_finished() must reset target_fname to
 * aव्योम that the file can be incorrectly हटाओd upon resume, since the faked
 * CANCEL_FCOPY message is spurious in this हाल.
 */
अटल पूर्णांक hv_copy_finished(व्योम)
अणु
	बंद(target_fd);
	target_fname[0] = '\0';
	वापस 0;
पूर्ण
अटल पूर्णांक hv_copy_cancel(व्योम)
अणु
	बंद(target_fd);
	अगर (म_माप(target_fname) > 0) अणु
		unlink(target_fname);
		target_fname[0] = '\0';
	पूर्ण
	वापस 0;

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
	पूर्णांक fcopy_fd = -1;
	पूर्णांक error;
	पूर्णांक daemonize = 1, दीर्घ_index = 0, opt;
	पूर्णांक version = FCOPY_CURRENT_VERSION;
	जोड़ अणु
		काष्ठा hv_fcopy_hdr hdr;
		काष्ठा hv_start_fcopy start;
		काष्ठा hv_करो_fcopy copy;
		__u32 kernel_modver;
	पूर्ण buffer = अणु पूर्ण;
	पूर्णांक in_handshake;

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
		शेष:
			prपूर्णांक_usage(argv);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	अगर (daemonize && daemon(1, 0)) अणु
		syslog(LOG_ERR, "daemon() failed; error: %s", म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	खोलोlog("HV_FCOPY", 0, LOG_USER);
	syslog(LOG_INFO, "starting; pid is:%d", getpid());

reखोलो_fcopy_fd:
	अगर (fcopy_fd != -1)
		बंद(fcopy_fd);
	/* Remove any possible partially-copied file on error */
	hv_copy_cancel();
	in_handshake = 1;
	fcopy_fd = खोलो("/dev/vmbus/hv_fcopy", O_RDWR);

	अगर (fcopy_fd < 0) अणु
		syslog(LOG_ERR, "open /dev/vmbus/hv_fcopy failed; error: %d %s",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	/*
	 * Register with the kernel.
	 */
	अगर ((ग_लिखो(fcopy_fd, &version, माप(पूर्णांक))) != माप(पूर्णांक)) अणु
		syslog(LOG_ERR, "Registration failed: %s", म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	जबतक (1) अणु
		/*
		 * In this loop we process fcopy messages after the
		 * handshake is complete.
		 */
		sमाप_प्रकार len;

		len = pपढ़ो(fcopy_fd, &buffer, माप(buffer), 0);
		अगर (len < 0) अणु
			syslog(LOG_ERR, "pread failed: %s", म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_fcopy_fd;
		पूर्ण

		अगर (in_handshake) अणु
			अगर (len != माप(buffer.kernel_modver)) अणु
				syslog(LOG_ERR, "invalid version negotiation");
				निकास(निकास_त्रुटि);
			पूर्ण
			in_handshake = 0;
			syslog(LOG_INFO, "kernel module version: %u",
			       buffer.kernel_modver);
			जारी;
		पूर्ण

		चयन (buffer.hdr.operation) अणु
		हाल START_खाता_COPY:
			error = hv_start_fcopy(&buffer.start);
			अवरोध;
		हाल WRITE_TO_खाता:
			error = hv_copy_data(&buffer.copy);
			अवरोध;
		हाल COMPLETE_FCOPY:
			error = hv_copy_finished();
			अवरोध;
		हाल CANCEL_FCOPY:
			error = hv_copy_cancel();
			अवरोध;

		शेष:
			error = HV_E_FAIL;
			syslog(LOG_ERR, "Unknown operation: %d",
				buffer.hdr.operation);

		पूर्ण

		/*
		 * pग_लिखो() may वापस an error due to the faked CANCEL_FCOPY
		 * message upon hibernation. Ignore the error by resetting the
		 * dev file, i.e. closing and re-खोलोing it.
		 */
		अगर (pग_लिखो(fcopy_fd, &error, माप(पूर्णांक), 0) != माप(पूर्णांक)) अणु
			syslog(LOG_ERR, "pwrite failed: %s", म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_fcopy_fd;
		पूर्ण
	पूर्ण
पूर्ण
