<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2005-2020 IBM Corporation.
 *
 * Includes code from librtas (https://github.com/ibm-घातer-utilities/librtas/)
 */

#समावेश <byteswap.h>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश "utils.h"

#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#घोषणा cpu_to_be32(x)		bswap_32(x)
#घोषणा be32_to_cpu(x)		bswap_32(x)
#अन्यथा
#घोषणा cpu_to_be32(x)		(x)
#घोषणा be32_to_cpu(x)		(x)
#पूर्ण_अगर

#घोषणा RTAS_IO_ASSERT	-1098	/* Unexpected I/O Error */
#घोषणा RTAS_UNKNOWN_OP -1099	/* No Firmware Implementation of Function */
#घोषणा BLOCK_SIZE 4096
#घोषणा PAGE_SIZE 4096
#घोषणा MAX_PAGES 64

अटल स्थिर अक्षर *ofdt_rtas_path = "/proc/device-tree/rtas";

प्रकार __be32 uपूर्णांक32_t;
काष्ठा rtas_args अणु
	__be32 token;
	__be32 nargs;
	__be32 nret;
	__be32 args[16];
	__be32 *rets;	  /* Poपूर्णांकer to वापस values in args[]. */
पूर्ण;

काष्ठा region अणु
	uपूर्णांक64_t addr;
	uपूर्णांक32_t size;
	काष्ठा region *next;
पूर्ण;

पूर्णांक पढ़ो_entire_file(पूर्णांक fd, अक्षर **buf, माप_प्रकार *len)
अणु
	माप_प्रकार buf_size = 0;
	माप_प्रकार off = 0;
	पूर्णांक rc;

	*buf = शून्य;
	करो अणु
		buf_size += BLOCK_SIZE;
		अगर (*buf == शून्य)
			*buf = दो_स्मृति(buf_size);
		अन्यथा
			*buf = पुनः_स्मृति(*buf, buf_size);

		अगर (*buf == शून्य)
			वापस -ENOMEM;

		rc = पढ़ो(fd, *buf + off, BLOCK_SIZE);
		अगर (rc < 0)
			वापस -EIO;

		off += rc;
	पूर्ण जबतक (rc == BLOCK_SIZE);

	अगर (len)
		*len = off;

	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_prop_file(स्थिर अक्षर *prop_path, स्थिर अक्षर *prop_name, पूर्णांक *fd)
अणु
	अक्षर *path;
	पूर्णांक len;

	/* allocate enough क्रम two string, a slash and trailing शून्य */
	len = म_माप(prop_path) + म_माप(prop_name) + 1 + 1;
	path = दो_स्मृति(len);
	अगर (path == शून्य)
		वापस -ENOMEM;

	snम_लिखो(path, len, "%s/%s", prop_path, prop_name);

	*fd = खोलो(path, O_RDONLY);
	मुक्त(path);
	अगर (*fd < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

अटल पूर्णांक get_property(स्थिर अक्षर *prop_path, स्थिर अक्षर *prop_name,
			अक्षर **prop_val, माप_प्रकार *prop_len)
अणु
	पूर्णांक rc, fd;

	rc = खोलो_prop_file(prop_path, prop_name, &fd);
	अगर (rc)
		वापस rc;

	rc = पढ़ो_entire_file(fd, prop_val, prop_len);
	बंद(fd);

	वापस rc;
पूर्ण

पूर्णांक rtas_token(स्थिर अक्षर *call_name)
अणु
	अक्षर *prop_buf = शून्य;
	माप_प्रकार len;
	पूर्णांक rc;

	rc = get_property(ofdt_rtas_path, call_name, &prop_buf, &len);
	अगर (rc < 0) अणु
		rc = RTAS_UNKNOWN_OP;
		जाओ err;
	पूर्ण

	rc = be32_to_cpu(*(पूर्णांक *)prop_buf);

err:
	मुक्त(prop_buf);
	वापस rc;
पूर्ण

अटल पूर्णांक पढ़ो_kregion_bounds(काष्ठा region *kregion)
अणु
	अक्षर *buf;
	पूर्णांक fd;
	पूर्णांक rc;

	fd = खोलो("/proc/ppc64/rtas/rmo_buffer", O_RDONLY);
	अगर (fd < 0) अणु
		म_लिखो("Could not open rmo_buffer file\n");
		वापस RTAS_IO_ASSERT;
	पूर्ण

	rc = पढ़ो_entire_file(fd, &buf, शून्य);
	बंद(fd);
	अगर (rc) अणु
		मुक्त(buf);
		वापस rc;
	पूर्ण

	माला_पूछो(buf, "%" SCNx64 " %x", &kregion->addr, &kregion->size);
	मुक्त(buf);

	अगर (!(kregion->size && kregion->addr) ||
	    (kregion->size > (PAGE_SIZE * MAX_PAGES))) अणु
		म_लिखो("Unexpected kregion bounds\n");
		वापस RTAS_IO_ASSERT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtas_call(स्थिर अक्षर *name, पूर्णांक nargs,
		     पूर्णांक nrets, ...)
अणु
	काष्ठा rtas_args args;
	__be32 *rets[16];
	पूर्णांक i, rc, token;
	बहु_सूची ap;

	बहु_शुरू(ap, nrets);

	token = rtas_token(name);
	अगर (token == RTAS_UNKNOWN_OP) अणु
		// We करोn't care if the call doesn't exist
		म_लिखो("call '%s' not available, skipping...", name);
		rc = RTAS_UNKNOWN_OP;
		जाओ err;
	पूर्ण

	args.token = cpu_to_be32(token);
	args.nargs = cpu_to_be32(nargs);
	args.nret = cpu_to_be32(nrets);

	क्रम (i = 0; i < nargs; i++)
		args.args[i] = (__be32) बहु_तर्क(ap, अचिन्हित दीर्घ);

	क्रम (i = 0; i < nrets; i++)
		rets[i] = (__be32 *) बहु_तर्क(ap, अचिन्हित दीर्घ);

	rc = syscall(__NR_rtas, &args);
	अगर (rc) अणु
		rc = -त्रुटि_सं;
		जाओ err;
	पूर्ण

	अगर (nrets) अणु
		*(rets[0]) = be32_to_cpu(args.args[nargs]);

		क्रम (i = 1; i < nrets; i++) अणु
			*(rets[i]) = args.args[nargs + i];
		पूर्ण
	पूर्ण

err:
	बहु_पूर्ण(ap);
	वापस rc;
पूर्ण

अटल पूर्णांक test(व्योम)
अणु
	काष्ठा region rmo_region;
	uपूर्णांक32_t rmo_start;
	uपूर्णांक32_t rmo_end;
	__be32 rets[1];
	पूर्णांक rc;

	// Test a legitimate harmless call
	// Expected: call succeeds
	म_लिखो("Test a permitted call, no parameters... ");
	rc = rtas_call("get-time-of-day", 0, 1, rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != 0 && rc != RTAS_UNKNOWN_OP);

	// Test a prohibited call
	// Expected: call वापसs -EINVAL
	म_लिखो("Test a prohibited call... ");
	rc = rtas_call("nvram-fetch", 0, 1, rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != -EINVAL && rc != RTAS_UNKNOWN_OP);

	// Get RMO
	rc = पढ़ो_kregion_bounds(&rmo_region);
	अगर (rc) अणु
		म_लिखो("Couldn't read RMO region bounds, skipping remaining cases\n");
		वापस 0;
	पूर्ण
	rmo_start = rmo_region.addr;
	rmo_end = rmo_start + rmo_region.size - 1;
	म_लिखो("RMO range: %08x - %08x\n", rmo_start, rmo_end);

	// Test a permitted call, user-supplied size, buffer inside RMO
	// Expected: call succeeds
	म_लिखो("Test a permitted call, user-supplied size, buffer inside RMO... ");
	rc = rtas_call("ibm,get-system-parameter", 3, 1, 0, cpu_to_be32(rmo_start),
		       cpu_to_be32(rmo_end - rmo_start + 1), rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != 0 && rc != RTAS_UNKNOWN_OP);

	// Test a permitted call, user-supplied size, buffer start outside RMO
	// Expected: call वापसs -EINVAL
	म_लिखो("Test a permitted call, user-supplied size, buffer start outside RMO... ");
	rc = rtas_call("ibm,get-system-parameter", 3, 1, 0, cpu_to_be32(rmo_end + 1),
		       cpu_to_be32(4000), rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != -EINVAL && rc != RTAS_UNKNOWN_OP);

	// Test a permitted call, user-supplied size, buffer end outside RMO
	// Expected: call वापसs -EINVAL
	म_लिखो("Test a permitted call, user-supplied size, buffer end outside RMO... ");
	rc = rtas_call("ibm,get-system-parameter", 3, 1, 0, cpu_to_be32(rmo_start),
		       cpu_to_be32(rmo_end - rmo_start + 2), rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != -EINVAL && rc != RTAS_UNKNOWN_OP);

	// Test a permitted call, fixed size, buffer end outside RMO
	// Expected: call वापसs -EINVAL
	म_लिखो("Test a permitted call, fixed size, buffer end outside RMO... ");
	rc = rtas_call("ibm,configure-connector", 2, 1, cpu_to_be32(rmo_end - 4000), 0, rets);
	म_लिखो("rc: %d\n", rc);
	FAIL_IF(rc != -EINVAL && rc != RTAS_UNKNOWN_OP);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test, "rtas_filter");
पूर्ण
