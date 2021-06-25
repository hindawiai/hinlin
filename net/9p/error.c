<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/9p/error.c
 *
 * Error string handling
 *
 * Plan 9 uses error strings, Unix uses error numbers.  These functions
 * try to help manage that and provide क्रम dynamically adding error
 * mappings.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/jhash.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/9p/9p.h>

/**
 * काष्ठा errormap - map string errors from Plan 9 to Linux numeric ids
 * @name: string sent over 9P
 * @val: numeric id most बंदly representing @name
 * @namelen: length of string
 * @list: hash-table list क्रम string lookup
 */
काष्ठा errormap अणु
	अक्षर *name;
	पूर्णांक val;

	पूर्णांक namelen;
	काष्ठा hlist_node list;
पूर्ण;

#घोषणा ERRHASHSZ		32
अटल काष्ठा hlist_head hash_errmap[ERRHASHSZ];

/* FixMe - reduce to a reasonable size */
अटल काष्ठा errormap errmap[] = अणु
	अणु"Operation not permitted", EPERMपूर्ण,
	अणु"wstat prohibited", EPERMपूर्ण,
	अणु"No such file or directory", ENOENTपूर्ण,
	अणु"directory entry not found", ENOENTपूर्ण,
	अणु"file not found", ENOENTपूर्ण,
	अणु"Interrupted system call", EINTRपूर्ण,
	अणु"Input/output error", EIOपूर्ण,
	अणु"No such device or address", ENXIOपूर्ण,
	अणु"Argument list too long", E2BIGपूर्ण,
	अणु"Bad file descriptor", EBADFपूर्ण,
	अणु"Resource temporarily unavailable", EAGAINपूर्ण,
	अणु"Cannot allocate memory", ENOMEMपूर्ण,
	अणु"Permission denied", EACCESपूर्ण,
	अणु"Bad address", EFAULTपूर्ण,
	अणु"Block device required", ENOTBLKपूर्ण,
	अणु"Device or resource busy", EBUSYपूर्ण,
	अणु"File exists", EEXISTपूर्ण,
	अणु"Invalid cross-device link", EXDEVपूर्ण,
	अणु"No such device", ENODEVपूर्ण,
	अणु"Not a directory", ENOTसूचीपूर्ण,
	अणु"Is a directory", EISसूचीपूर्ण,
	अणु"Invalid argument", EINVALपूर्ण,
	अणु"Too many open files in system", ENखातापूर्ण,
	अणु"Too many open files", EMखातापूर्ण,
	अणु"Text file busy", ETXTBSYपूर्ण,
	अणु"File too large", EFBIGपूर्ण,
	अणु"No space left on device", ENOSPCपूर्ण,
	अणु"Illegal seek", ESPIPEपूर्ण,
	अणु"Read-only file system", EROFSपूर्ण,
	अणु"Too many links", EMLINKपूर्ण,
	अणु"Broken pipe", EPIPEपूर्ण,
	अणु"Numerical argument out of domain", गलत_तर्कपूर्ण,
	अणु"Numerical result out of range", दुस्फलपूर्ण,
	अणु"Resource deadlock avoided", EDEADLKपूर्ण,
	अणु"File name too long", ENAMETOOLONGपूर्ण,
	अणु"No locks available", ENOLCKपूर्ण,
	अणु"Function not implemented", ENOSYSपूर्ण,
	अणु"Directory not empty", ENOTEMPTYपूर्ण,
	अणु"Too many levels of symbolic links", ELOOPपूर्ण,
	अणु"No message of desired type", ENOMSGपूर्ण,
	अणु"Identifier removed", EIDRMपूर्ण,
	अणु"No data available", ENODATAपूर्ण,
	अणु"Machine is not on the network", ENONETपूर्ण,
	अणु"Package not installed", ENOPKGपूर्ण,
	अणु"Object is remote", EREMOTEपूर्ण,
	अणु"Link has been severed", ENOLINKपूर्ण,
	अणु"Communication error on send", ECOMMपूर्ण,
	अणु"Protocol error", EPROTOपूर्ण,
	अणु"Bad message", EBADMSGपूर्ण,
	अणु"File descriptor in bad state", EBADFDपूर्ण,
	अणु"Streams pipe error", ESTRPIPEपूर्ण,
	अणु"Too many users", EUSERSपूर्ण,
	अणु"Socket operation on non-socket", ENOTSOCKपूर्ण,
	अणु"Message too long", EMSGSIZEपूर्ण,
	अणु"Protocol not available", ENOPROTOOPTपूर्ण,
	अणु"Protocol not supported", EPROTONOSUPPORTपूर्ण,
	अणु"Socket type not supported", ESOCKTNOSUPPORTपूर्ण,
	अणु"Operation not supported", EOPNOTSUPPपूर्ण,
	अणु"Protocol family not supported", EPFNOSUPPORTपूर्ण,
	अणु"Network is down", ENETDOWNपूर्ण,
	अणु"Network is unreachable", ENETUNREACHपूर्ण,
	अणु"Network dropped connection on reset", ENETRESETपूर्ण,
	अणु"Software caused connection abort", ECONNABORTEDपूर्ण,
	अणु"Connection reset by peer", ECONNRESETपूर्ण,
	अणु"No buffer space available", ENOBUFSपूर्ण,
	अणु"Transport endpoint is already connected", EISCONNपूर्ण,
	अणु"Transport endpoint is not connected", ENOTCONNपूर्ण,
	अणु"Cannot send after transport endpoint shutdown", ESHUTDOWNपूर्ण,
	अणु"Connection timed out", ETIMEDOUTपूर्ण,
	अणु"Connection refused", ECONNREFUSEDपूर्ण,
	अणु"Host is down", EHOSTDOWNपूर्ण,
	अणु"No route to host", EHOSTUNREACHपूर्ण,
	अणु"Operation already in progress", EALREADYपूर्ण,
	अणु"Operation now in progress", EINPROGRESSपूर्ण,
	अणु"Is a named type file", EISNAMपूर्ण,
	अणु"Remote I/O error", EREMOTEIOपूर्ण,
	अणु"Disk quota exceeded", EDQUOTपूर्ण,
/* errors from fossil, vacfs, and u9fs */
	अणु"fid unknown or out of range", EBADFपूर्ण,
	अणु"permission denied", EACCESपूर्ण,
	अणु"file does not exist", ENOENTपूर्ण,
	अणु"authentication failed", ECONNREFUSEDपूर्ण,
	अणु"bad offset in directory read", ESPIPEपूर्ण,
	अणु"bad use of fid", EBADFपूर्ण,
	अणु"wstat can't convert between files and directories", EPERMपूर्ण,
	अणु"directory is not empty", ENOTEMPTYपूर्ण,
	अणु"file exists", EEXISTपूर्ण,
	अणु"file already exists", EEXISTपूर्ण,
	अणु"file or directory already exists", EEXISTपूर्ण,
	अणु"fid already in use", EBADFपूर्ण,
	अणु"file in use", ETXTBSYपूर्ण,
	अणु"i/o error", EIOपूर्ण,
	अणु"file already open for I/O", ETXTBSYपूर्ण,
	अणु"illegal mode", EINVALपूर्ण,
	अणु"illegal name", ENAMETOOLONGपूर्ण,
	अणु"not a directory", ENOTसूचीपूर्ण,
	अणु"not a member of proposed group", EPERMपूर्ण,
	अणु"not owner", EACCESपूर्ण,
	अणु"only owner can change group in wstat", EACCESपूर्ण,
	अणु"read only file system", EROFSपूर्ण,
	अणु"no access to special file", EPERMपूर्ण,
	अणु"i/o count too large", EIOपूर्ण,
	अणु"unknown group", EINVALपूर्ण,
	अणु"unknown user", EINVALपूर्ण,
	अणु"bogus wstat buffer", EPROTOपूर्ण,
	अणु"exclusive use file already open", EAGAINपूर्ण,
	अणु"corrupted directory entry", EIOपूर्ण,
	अणु"corrupted file entry", EIOपूर्ण,
	अणु"corrupted block label", EIOपूर्ण,
	अणु"corrupted meta data", EIOपूर्ण,
	अणु"illegal offset", EINVALपूर्ण,
	अणु"illegal path element", ENOENTपूर्ण,
	अणु"root of file system is corrupted", EIOपूर्ण,
	अणु"corrupted super block", EIOपूर्ण,
	अणु"protocol botch", EPROTOपूर्ण,
	अणु"file system is full", ENOSPCपूर्ण,
	अणु"file is in use", EAGAINपूर्ण,
	अणु"directory entry is not allocated", ENOENTपूर्ण,
	अणु"file is read only", EROFSपूर्ण,
	अणु"file has been removed", EIDRMपूर्ण,
	अणु"only support truncation to zero length", EPERMपूर्ण,
	अणु"cannot remove root", EPERMपूर्ण,
	अणु"file too big", EFBIGपूर्ण,
	अणु"venti i/o error", EIOपूर्ण,
	/* these are not errors */
	अणु"u9fs rhostsauth: no authentication required", 0पूर्ण,
	अणु"u9fs authnone: no authentication required", 0पूर्ण,
	अणुशून्य, -1पूर्ण
पूर्ण;

/**
 * p9_error_init - preload mappings पूर्णांकo hash list
 *
 */

पूर्णांक p9_error_init(व्योम)
अणु
	काष्ठा errormap *c;
	पूर्णांक bucket;

	/* initialize hash table */
	क्रम (bucket = 0; bucket < ERRHASHSZ; bucket++)
		INIT_HLIST_HEAD(&hash_errmap[bucket]);

	/* load initial error map पूर्णांकo hash table */
	क्रम (c = errmap; c->name != शून्य; c++) अणु
		c->namelen = म_माप(c->name);
		bucket = jhash(c->name, c->namelen, 0) % ERRHASHSZ;
		INIT_HLIST_NODE(&c->list);
		hlist_add_head(&c->list, &hash_errmap[bucket]);
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(p9_error_init);

/**
 * p9_errstr2त्रुटि_सं - convert error string to error number
 * @errstr: error string
 * @len: length of error string
 *
 */

पूर्णांक p9_errstr2त्रुटि_सं(अक्षर *errstr, पूर्णांक len)
अणु
	पूर्णांक त्रुटि_सं;
	काष्ठा errormap *c;
	पूर्णांक bucket;

	त्रुटि_सं = 0;
	c = शून्य;
	bucket = jhash(errstr, len, 0) % ERRHASHSZ;
	hlist_क्रम_each_entry(c, &hash_errmap[bucket], list) अणु
		अगर (c->namelen == len && !स_भेद(c->name, errstr, len)) अणु
			त्रुटि_सं = c->val;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (त्रुटि_सं == 0) अणु
		/* TODO: अगर error isn't found, add it dynamically */
		errstr[len] = 0;
		pr_err("%s: server reported unknown error %s\n",
		       __func__, errstr);
		त्रुटि_सं = ESERVERFAULT;
	पूर्ण

	वापस -त्रुटि_सं;
पूर्ण
EXPORT_SYMBOL(p9_errstr2त्रुटि_सं);
