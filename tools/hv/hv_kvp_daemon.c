<शैली गुरु>
/*
 * An implementation of key value pair (KVP) functionality क्रम Linux.
 *
 *
 * Copyright (C) 2010, Novell, Inc.
 * Author : K. Y. Srinivasan <ksrinivasan@novell.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 */


#समावेश <sys/poll.h>
#समावेश <sys/utsname.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <arpa/inet.h>
#समावेश <linux/hyperv.h>
#समावेश <अगरaddrs.h>
#समावेश <netdb.h>
#समावेश <syslog.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <dirent.h>
#समावेश <net/अगर.h>
#समावेश <सीमा.स>
#समावेश <getopt.h>

/*
 * KVP protocol: The user mode component first रेजिस्टरs with the
 * the kernel component. Subsequently, the kernel component requests, data
 * क्रम the specअगरied keys. In response to this message the user mode component
 * fills in the value corresponding to the specअगरied key. We overload the
 * sequence field in the cn_msg header to define our KVP message types.
 *
 * We use this infraकाष्ठाure क्रम also supporting queries from user mode
 * application क्रम state that may be मुख्यtained in the KVP kernel component.
 *
 */


क्रमागत key_index अणु
	FullyQualअगरiedDoमुख्यName = 0,
	IntegrationServicesVersion, /*This key is serviced in the kernel*/
	NetworkAddressIPv4,
	NetworkAddressIPv6,
	OSBuildNumber,
	OSName,
	OSMajorVersion,
	OSMinorVersion,
	OSVersion,
	ProcessorArchitecture
पूर्ण;


क्रमागत अणु
	IPADDR = 0,
	NETMASK,
	GATEWAY,
	DNS
पूर्ण;

अटल पूर्णांक in_hand_shake;

अटल अक्षर *os_name = "";
अटल अक्षर *os_major = "";
अटल अक्षर *os_minor = "";
अटल अक्षर *processor_arch;
अटल अक्षर *os_build;
अटल अक्षर *os_version;
अटल अक्षर *lic_version = "Unknown version";
अटल अक्षर full_करोमुख्य_name[HV_KVP_EXCHANGE_MAX_VALUE_SIZE];
अटल काष्ठा utsname uts_buf;

/*
 * The location of the पूर्णांकerface configuration file.
 */

#घोषणा KVP_CONFIG_LOC	"/var/lib/hyperv"

#अगर_अघोषित KVP_SCRIPTS_PATH
#घोषणा KVP_SCRIPTS_PATH "/usr/libexec/hypervkvpd/"
#पूर्ण_अगर

#घोषणा KVP_NET_सूची "/sys/class/net/"

#घोषणा MAX_खाता_NAME 100
#घोषणा ENTRIES_PER_BLOCK 50

काष्ठा kvp_record अणु
	अक्षर key[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
	अक्षर value[HV_KVP_EXCHANGE_MAX_VALUE_SIZE];
पूर्ण;

काष्ठा kvp_file_state अणु
	पूर्णांक fd;
	पूर्णांक num_blocks;
	काष्ठा kvp_record *records;
	पूर्णांक num_records;
	अक्षर fname[MAX_खाता_NAME];
पूर्ण;

अटल काष्ठा kvp_file_state kvp_file_info[KVP_POOL_COUNT];

अटल व्योम kvp_acquire_lock(पूर्णांक pool)
अणु
	काष्ठा flock fl = अणुF_WRLCK, शुरू_से, 0, 0, 0पूर्ण;
	fl.l_pid = getpid();

	अगर (fcntl(kvp_file_info[pool].fd, F_SETLKW, &fl) == -1) अणु
		syslog(LOG_ERR, "Failed to acquire the lock pool: %d; error: %d %s", pool,
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम kvp_release_lock(पूर्णांक pool)
अणु
	काष्ठा flock fl = अणुF_UNLCK, शुरू_से, 0, 0, 0पूर्ण;
	fl.l_pid = getpid();

	अगर (fcntl(kvp_file_info[pool].fd, F_SETLK, &fl) == -1) अणु
		syslog(LOG_ERR, "Failed to release the lock pool: %d; error: %d %s", pool,
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम kvp_update_file(पूर्णांक pool)
अणु
	खाता *filep;

	/*
	 * We are going to ग_लिखो our in-memory registry out to
	 * disk; acquire the lock first.
	 */
	kvp_acquire_lock(pool);

	filep = ख_खोलो(kvp_file_info[pool].fname, "we");
	अगर (!filep) अणु
		syslog(LOG_ERR, "Failed to open file, pool: %d; error: %d %s", pool,
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		kvp_release_lock(pool);
		निकास(निकास_त्रुटि);
	पूर्ण

	ख_डालो(kvp_file_info[pool].records, माप(काष्ठा kvp_record),
				kvp_file_info[pool].num_records, filep);

	अगर (ख_त्रुटि(filep) || ख_बंद(filep)) अणु
		kvp_release_lock(pool);
		syslog(LOG_ERR, "Failed to write file, pool: %d", pool);
		निकास(निकास_त्रुटि);
	पूर्ण

	kvp_release_lock(pool);
पूर्ण

अटल व्योम kvp_update_mem_state(पूर्णांक pool)
अणु
	खाता *filep;
	माप_प्रकार records_पढ़ो = 0;
	काष्ठा kvp_record *record = kvp_file_info[pool].records;
	काष्ठा kvp_record *पढ़ोp;
	पूर्णांक num_blocks = kvp_file_info[pool].num_blocks;
	पूर्णांक alloc_unit = माप(काष्ठा kvp_record) * ENTRIES_PER_BLOCK;

	kvp_acquire_lock(pool);

	filep = ख_खोलो(kvp_file_info[pool].fname, "re");
	अगर (!filep) अणु
		syslog(LOG_ERR, "Failed to open file, pool: %d; error: %d %s", pool,
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		kvp_release_lock(pool);
		निकास(निकास_त्रुटि);
	पूर्ण
	क्रम (;;) अणु
		पढ़ोp = &record[records_पढ़ो];
		records_पढ़ो += ख_पढ़ो(पढ़ोp, माप(काष्ठा kvp_record),
				ENTRIES_PER_BLOCK * num_blocks - records_पढ़ो,
				filep);

		अगर (ख_त्रुटि(filep)) अणु
			syslog(LOG_ERR,
				"Failed to read file, pool: %d; error: %d %s",
				 pool, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			kvp_release_lock(pool);
			निकास(निकास_त्रुटि);
		पूर्ण

		अगर (!ख_पूर्ण(filep)) अणु
			/*
			 * We have more data to पढ़ो.
			 */
			num_blocks++;
			record = पुनः_स्मृति(record, alloc_unit * num_blocks);

			अगर (record == शून्य) अणु
				syslog(LOG_ERR, "malloc failed");
				kvp_release_lock(pool);
				निकास(निकास_त्रुटि);
			पूर्ण
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	kvp_file_info[pool].num_blocks = num_blocks;
	kvp_file_info[pool].records = record;
	kvp_file_info[pool].num_records = records_पढ़ो;

	ख_बंद(filep);
	kvp_release_lock(pool);
पूर्ण

अटल पूर्णांक kvp_file_init(व्योम)
अणु
	पूर्णांक  fd;
	अक्षर *fname;
	पूर्णांक i;
	पूर्णांक alloc_unit = माप(काष्ठा kvp_record) * ENTRIES_PER_BLOCK;

	अगर (access(KVP_CONFIG_LOC, F_OK)) अणु
		अगर (सूची_गढ़ो(KVP_CONFIG_LOC, 0755 /* rwxr-xr-x */)) अणु
			syslog(LOG_ERR, "Failed to create '%s'; error: %d %s", KVP_CONFIG_LOC,
					त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < KVP_POOL_COUNT; i++) अणु
		fname = kvp_file_info[i].fname;
		प्र_लिखो(fname, "%s/.kvp_pool_%d", KVP_CONFIG_LOC, i);
		fd = खोलो(fname, O_RDWR | O_CREAT | O_CLOEXEC, 0644 /* rw-r--r-- */);

		अगर (fd == -1)
			वापस 1;

		kvp_file_info[i].fd = fd;
		kvp_file_info[i].num_blocks = 1;
		kvp_file_info[i].records = दो_स्मृति(alloc_unit);
		अगर (kvp_file_info[i].records == शून्य)
			वापस 1;
		kvp_file_info[i].num_records = 0;
		kvp_update_mem_state(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvp_key_delete(पूर्णांक pool, स्थिर __u8 *key, पूर्णांक key_size)
अणु
	पूर्णांक i;
	पूर्णांक j, k;
	पूर्णांक num_records;
	काष्ठा kvp_record *record;

	/*
	 * First update the in-memory state.
	 */
	kvp_update_mem_state(pool);

	num_records = kvp_file_info[pool].num_records;
	record = kvp_file_info[pool].records;

	क्रम (i = 0; i < num_records; i++) अणु
		अगर (स_भेद(key, record[i].key, key_size))
			जारी;
		/*
		 * Found a match; just move the reमुख्यing
		 * entries up.
		 */
		अगर (i == (num_records - 1)) अणु
			kvp_file_info[pool].num_records--;
			kvp_update_file(pool);
			वापस 0;
		पूर्ण

		j = i;
		k = j + 1;
		क्रम (; k < num_records; k++) अणु
			म_नकल(record[j].key, record[k].key);
			म_नकल(record[j].value, record[k].value);
			j++;
		पूर्ण

		kvp_file_info[pool].num_records--;
		kvp_update_file(pool);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक kvp_key_add_or_modअगरy(पूर्णांक pool, स्थिर __u8 *key, पूर्णांक key_size,
				 स्थिर __u8 *value, पूर्णांक value_size)
अणु
	पूर्णांक i;
	पूर्णांक num_records;
	काष्ठा kvp_record *record;
	पूर्णांक num_blocks;

	अगर ((key_size > HV_KVP_EXCHANGE_MAX_KEY_SIZE) ||
		(value_size > HV_KVP_EXCHANGE_MAX_VALUE_SIZE))
		वापस 1;

	/*
	 * First update the in-memory state.
	 */
	kvp_update_mem_state(pool);

	num_records = kvp_file_info[pool].num_records;
	record = kvp_file_info[pool].records;
	num_blocks = kvp_file_info[pool].num_blocks;

	क्रम (i = 0; i < num_records; i++) अणु
		अगर (स_भेद(key, record[i].key, key_size))
			जारी;
		/*
		 * Found a match; just update the value -
		 * this is the modअगरy हाल.
		 */
		स_नकल(record[i].value, value, value_size);
		kvp_update_file(pool);
		वापस 0;
	पूर्ण

	/*
	 * Need to add a new entry;
	 */
	अगर (num_records == (ENTRIES_PER_BLOCK * num_blocks)) अणु
		/* Need to allocate a larger array क्रम reg entries. */
		record = पुनः_स्मृति(record, माप(काष्ठा kvp_record) *
			 ENTRIES_PER_BLOCK * (num_blocks + 1));

		अगर (record == शून्य)
			वापस 1;
		kvp_file_info[pool].num_blocks++;

	पूर्ण
	स_नकल(record[i].value, value, value_size);
	स_नकल(record[i].key, key, key_size);
	kvp_file_info[pool].records = record;
	kvp_file_info[pool].num_records++;
	kvp_update_file(pool);
	वापस 0;
पूर्ण

अटल पूर्णांक kvp_get_value(पूर्णांक pool, स्थिर __u8 *key, पूर्णांक key_size, __u8 *value,
			पूर्णांक value_size)
अणु
	पूर्णांक i;
	पूर्णांक num_records;
	काष्ठा kvp_record *record;

	अगर ((key_size > HV_KVP_EXCHANGE_MAX_KEY_SIZE) ||
		(value_size > HV_KVP_EXCHANGE_MAX_VALUE_SIZE))
		वापस 1;

	/*
	 * First update the in-memory state.
	 */
	kvp_update_mem_state(pool);

	num_records = kvp_file_info[pool].num_records;
	record = kvp_file_info[pool].records;

	क्रम (i = 0; i < num_records; i++) अणु
		अगर (स_भेद(key, record[i].key, key_size))
			जारी;
		/*
		 * Found a match; just copy the value out.
		 */
		स_नकल(value, record[i].value, value_size);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक kvp_pool_क्रमागतerate(पूर्णांक pool, पूर्णांक index, __u8 *key, पूर्णांक key_size,
				__u8 *value, पूर्णांक value_size)
अणु
	काष्ठा kvp_record *record;

	/*
	 * First update our in-memory database.
	 */
	kvp_update_mem_state(pool);
	record = kvp_file_info[pool].records;

	अगर (index >= kvp_file_info[pool].num_records) अणु
		वापस 1;
	पूर्ण

	स_नकल(key, record[index].key, key_size);
	स_नकल(value, record[index].value, value_size);
	वापस 0;
पूर्ण


व्योम kvp_get_os_info(व्योम)
अणु
	खाता	*file;
	अक्षर	*p, buf[512];

	uname(&uts_buf);
	os_version = uts_buf.release;
	os_build = strdup(uts_buf.release);

	os_name = uts_buf.sysname;
	processor_arch = uts_buf.machine;

	/*
	 * The current winकरोws host (win7) expects the build
	 * string to be of the क्रमm: x.y.z
	 * Strip additional inक्रमmation we may have.
	 */
	p = म_अक्षर(os_version, '-');
	अगर (p)
		*p = '\0';

	/*
	 * Parse the /etc/os-release file अगर present:
	 * https://www.मुक्तdesktop.org/software/प्रणालीd/man/os-release.hपंचांगl
	 */
	file = ख_खोलो("/etc/os-release", "r");
	अगर (file != शून्य) अणु
		जबतक (ख_माला_लो(buf, माप(buf), file)) अणु
			अक्षर *value, *q;

			/* Ignore comments */
			अगर (buf[0] == '#')
				जारी;

			/* Split पूर्णांकo name=value */
			p = म_अक्षर(buf, '=');
			अगर (!p)
				जारी;
			*p++ = 0;

			/* Remove quotes and newline; un-escape */
			value = p;
			q = p;
			जबतक (*p) अणु
				अगर (*p == '\\') अणु
					++p;
					अगर (!*p)
						अवरोध;
					*q++ = *p++;
				पूर्ण अन्यथा अगर (*p == '\'' || *p == '"' ||
					   *p == '\n') अणु
					++p;
				पूर्ण अन्यथा अणु
					*q++ = *p++;
				पूर्ण
			पूर्ण
			*q = 0;

			अगर (!म_भेद(buf, "NAME")) अणु
				p = strdup(value);
				अगर (!p)
					अवरोध;
				os_name = p;
			पूर्ण अन्यथा अगर (!म_भेद(buf, "VERSION_ID")) अणु
				p = strdup(value);
				अगर (!p)
					अवरोध;
				os_major = p;
			पूर्ण
		पूर्ण
		ख_बंद(file);
		वापस;
	पूर्ण

	/* Fallback क्रम older RH/SUSE releases */
	file = ख_खोलो("/etc/SuSE-release", "r");
	अगर (file != शून्य)
		जाओ kvp_osinfo_found;
	file  = ख_खोलो("/etc/redhat-release", "r");
	अगर (file != शून्य)
		जाओ kvp_osinfo_found;

	/*
	 * We करोn't have inक्रमmation about the os.
	 */
	वापस;

kvp_osinfo_found:
	/* up to three lines */
	p = ख_माला_लो(buf, माप(buf), file);
	अगर (p) अणु
		p = म_अक्षर(buf, '\n');
		अगर (p)
			*p = '\0';
		p = strdup(buf);
		अगर (!p)
			जाओ करोne;
		os_name = p;

		/* second line */
		p = ख_माला_लो(buf, माप(buf), file);
		अगर (p) अणु
			p = म_अक्षर(buf, '\n');
			अगर (p)
				*p = '\0';
			p = strdup(buf);
			अगर (!p)
				जाओ करोne;
			os_major = p;

			/* third line */
			p = ख_माला_लो(buf, माप(buf), file);
			अगर (p)  अणु
				p = म_अक्षर(buf, '\n');
				अगर (p)
					*p = '\0';
				p = strdup(buf);
				अगर (p)
					os_minor = p;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	ख_बंद(file);
	वापस;
पूर्ण



/*
 * Retrieve an पूर्णांकerface name corresponding to the specअगरied guid.
 * If there is a match, the function वापसs a poपूर्णांकer
 * to the पूर्णांकerface name and अगर not, a शून्य is वापसed.
 * If a match is found, the caller is responsible क्रम
 * मुक्तing the memory.
 */

अटल अक्षर *kvp_get_अगर_name(अक्षर *guid)
अणु
	सूची *dir;
	काष्ठा dirent *entry;
	खाता    *file;
	अक्षर    *p, *x;
	अक्षर    *अगर_name = शून्य;
	अक्षर    buf[256];
	अक्षर dev_id[PATH_MAX];

	dir = सूची_खोलो(KVP_NET_सूची);
	अगर (dir == शून्य)
		वापस शून्य;

	जबतक ((entry = सूची_पढ़ो(dir)) != शून्य) अणु
		/*
		 * Set the state क्रम the next pass.
		 */
		snम_लिखो(dev_id, माप(dev_id), "%s%s/device/device_id",
			 KVP_NET_सूची, entry->d_name);

		file = ख_खोलो(dev_id, "r");
		अगर (file == शून्य)
			जारी;

		p = ख_माला_लो(buf, माप(buf), file);
		अगर (p) अणु
			x = म_अक्षर(p, '\n');
			अगर (x)
				*x = '\0';

			अगर (!म_भेद(p, guid)) अणु
				/*
				 * Found the guid match; वापस the पूर्णांकerface
				 * name. The caller will मुक्त the memory.
				 */
				अगर_name = strdup(entry->d_name);
				ख_बंद(file);
				अवरोध;
			पूर्ण
		पूर्ण
		ख_बंद(file);
	पूर्ण

	बंद_सूची(dir);
	वापस अगर_name;
पूर्ण

/*
 * Retrieve the MAC address given the पूर्णांकerface name.
 */

अटल अक्षर *kvp_अगर_name_to_mac(अक्षर *अगर_name)
अणु
	खाता    *file;
	अक्षर    *p, *x;
	अक्षर    buf[256];
	अक्षर addr_file[PATH_MAX];
	अचिन्हित पूर्णांक i;
	अक्षर *mac_addr = शून्य;

	snम_लिखो(addr_file, माप(addr_file), "%s%s%s", KVP_NET_सूची,
		 अगर_name, "/address");

	file = ख_खोलो(addr_file, "r");
	अगर (file == शून्य)
		वापस शून्य;

	p = ख_माला_लो(buf, माप(buf), file);
	अगर (p) अणु
		x = म_अक्षर(p, '\n');
		अगर (x)
			*x = '\0';
		क्रम (i = 0; i < म_माप(p); i++)
			p[i] = बड़े(p[i]);
		mac_addr = strdup(p);
	पूर्ण

	ख_बंद(file);
	वापस mac_addr;
पूर्ण

अटल व्योम kvp_process_ipconfig_file(अक्षर *cmd,
					अक्षर *config_buf, अचिन्हित पूर्णांक len,
					पूर्णांक element_size, पूर्णांक offset)
अणु
	अक्षर buf[256];
	अक्षर *p;
	अक्षर *x;
	खाता *file;

	/*
	 * First execute the command.
	 */
	file = pखोलो(cmd, "r");
	अगर (file == शून्य)
		वापस;

	अगर (offset == 0)
		स_रखो(config_buf, 0, len);
	जबतक ((p = ख_माला_लो(buf, माप(buf), file)) != शून्य) अणु
		अगर (len < म_माप(config_buf) + element_size + 1)
			अवरोध;

		x = म_अक्षर(p, '\n');
		अगर (x)
			*x = '\0';

		म_जोड़ो(config_buf, p);
		म_जोड़ो(config_buf, ";");
	पूर्ण
	pबंद(file);
पूर्ण

अटल व्योम kvp_get_ipconfig_info(अक्षर *अगर_name,
				 काष्ठा hv_kvp_ipaddr_value *buffer)
अणु
	अक्षर cmd[512];
	अक्षर dhcp_info[128];
	अक्षर *p;
	खाता *file;

	/*
	 * Get the address of शेष gateway (ipv4).
	 */
	प्र_लिखो(cmd, "%s %s", "ip route show dev", अगर_name);
	म_जोड़ो(cmd, " | awk '/default/ {print $3 }'");

	/*
	 * Execute the command to gather gateway info.
	 */
	kvp_process_ipconfig_file(cmd, (अक्षर *)buffer->gate_way,
				(MAX_GATEWAY_SIZE * 2), INET_ADDRSTRLEN, 0);

	/*
	 * Get the address of शेष gateway (ipv6).
	 */
	प्र_लिखो(cmd, "%s %s", "ip -f inet6  route show dev", अगर_name);
	म_जोड़ो(cmd, " | awk '/default/ {print $3 }'");

	/*
	 * Execute the command to gather gateway info (ipv6).
	 */
	kvp_process_ipconfig_file(cmd, (अक्षर *)buffer->gate_way,
				(MAX_GATEWAY_SIZE * 2), INET6_ADDRSTRLEN, 1);


	/*
	 * Gather the DNS state.
	 * Since there is no standard way to get this inक्रमmation
	 * across various distributions of पूर्णांकerest; we just invoke
	 * an बाह्यal script that needs to be ported across distros
	 * of पूर्णांकerest.
	 *
	 * Following is the expected क्रमmat of the inक्रमmation from the script:
	 *
	 * ipaddr1 (nameserver1)
	 * ipaddr2 (nameserver2)
	 * .
	 * .
	 */

	प्र_लिखो(cmd, KVP_SCRIPTS_PATH "%s",  "hv_get_dns_info");

	/*
	 * Execute the command to gather DNS info.
	 */
	kvp_process_ipconfig_file(cmd, (अक्षर *)buffer->dns_addr,
				(MAX_IP_ADDR_SIZE * 2), INET_ADDRSTRLEN, 0);

	/*
	 * Gather the DHCP state.
	 * We will gather this state by invoking an बाह्यal script.
	 * The parameter to the script is the पूर्णांकerface name.
	 * Here is the expected output:
	 *
	 * Enabled: DHCP enabled.
	 */

	प्र_लिखो(cmd, KVP_SCRIPTS_PATH "%s %s", "hv_get_dhcp_info", अगर_name);

	file = pखोलो(cmd, "r");
	अगर (file == शून्य)
		वापस;

	p = ख_माला_लो(dhcp_info, माप(dhcp_info), file);
	अगर (p == शून्य) अणु
		pबंद(file);
		वापस;
	पूर्ण

	अगर (!म_भेदन(p, "Enabled", 7))
		buffer->dhcp_enabled = 1;
	अन्यथा
		buffer->dhcp_enabled = 0;

	pबंद(file);
पूर्ण


अटल अचिन्हित पूर्णांक hweight32(अचिन्हित पूर्णांक *w)
अणु
	अचिन्हित पूर्णांक res = *w - ((*w >> 1) & 0x55555555);
	res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
	res = (res + (res >> 4)) & 0x0F0F0F0F;
	res = res + (res >> 8);
	वापस (res + (res >> 16)) & 0x000000FF;
पूर्ण

अटल पूर्णांक kvp_process_ip_address(व्योम *addrp,
				पूर्णांक family, अक्षर *buffer,
				पूर्णांक length,  पूर्णांक *offset)
अणु
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;
	पूर्णांक addr_length;
	अक्षर पंचांगp[50];
	स्थिर अक्षर *str;

	अगर (family == AF_INET) अणु
		addr = (काष्ठा sockaddr_in *)addrp;
		str = inet_ntop(family, &addr->sin_addr, पंचांगp, 50);
		addr_length = INET_ADDRSTRLEN;
	पूर्ण अन्यथा अणु
		addr6 = (काष्ठा sockaddr_in6 *)addrp;
		str = inet_ntop(family, &addr6->sin6_addr.s6_addr, पंचांगp, 50);
		addr_length = INET6_ADDRSTRLEN;
	पूर्ण

	अगर ((length - *offset) < addr_length + 2)
		वापस HV_E_FAIL;
	अगर (str == शून्य) अणु
		म_नकल(buffer, "inet_ntop failed\n");
		वापस HV_E_FAIL;
	पूर्ण
	अगर (*offset == 0)
		म_नकल(buffer, पंचांगp);
	अन्यथा अणु
		म_जोड़ो(buffer, ";");
		म_जोड़ो(buffer, पंचांगp);
	पूर्ण

	*offset += म_माप(str) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
kvp_get_ip_info(पूर्णांक family, अक्षर *अगर_name, पूर्णांक op,
		 व्योम  *out_buffer, अचिन्हित पूर्णांक length)
अणु
	काष्ठा अगरaddrs *अगरap;
	काष्ठा अगरaddrs *curp;
	पूर्णांक offset = 0;
	पूर्णांक sn_offset = 0;
	पूर्णांक error = 0;
	अक्षर *buffer;
	काष्ठा hv_kvp_ipaddr_value *ip_buffer = शून्य;
	अक्षर cidr_mask[5]; /* /xyz */
	पूर्णांक weight;
	पूर्णांक i;
	अचिन्हित पूर्णांक *w;
	अक्षर *sn_str;
	काष्ठा sockaddr_in6 *addr6;

	अगर (op == KVP_OP_ENUMERATE) अणु
		buffer = out_buffer;
	पूर्ण अन्यथा अणु
		ip_buffer = out_buffer;
		buffer = (अक्षर *)ip_buffer->ip_addr;
		ip_buffer->addr_family = 0;
	पूर्ण
	/*
	 * On entry पूर्णांकo this function, the buffer is capable of holding the
	 * maximum key value.
	 */

	अगर (getअगरaddrs(&अगरap)) अणु
		म_नकल(buffer, "getifaddrs failed\n");
		वापस HV_E_FAIL;
	पूर्ण

	curp = अगरap;
	जबतक (curp != शून्य) अणु
		अगर (curp->अगरa_addr == शून्य) अणु
			curp = curp->अगरa_next;
			जारी;
		पूर्ण

		अगर ((अगर_name != शून्य) &&
			(म_भेदन(curp->अगरa_name, अगर_name, म_माप(अगर_name)))) अणु
			/*
			 * We want info about a specअगरic पूर्णांकerface;
			 * just जारी.
			 */
			curp = curp->अगरa_next;
			जारी;
		पूर्ण

		/*
		 * We only support two address families: AF_INET and AF_INET6.
		 * If a family value of 0 is specअगरied, we collect both
		 * supported address families; अगर not we gather info on
		 * the specअगरied address family.
		 */
		अगर ((((family != 0) &&
			 (curp->अगरa_addr->sa_family != family))) ||
			 (curp->अगरa_flags & IFF_LOOPBACK)) अणु
			curp = curp->अगरa_next;
			जारी;
		पूर्ण
		अगर ((curp->अगरa_addr->sa_family != AF_INET) &&
			(curp->अगरa_addr->sa_family != AF_INET6)) अणु
			curp = curp->अगरa_next;
			जारी;
		पूर्ण

		अगर (op == KVP_OP_GET_IP_INFO) अणु
			/*
			 * Gather info other than the IP address.
			 * IP address info will be gathered later.
			 */
			अगर (curp->अगरa_addr->sa_family == AF_INET) अणु
				ip_buffer->addr_family |= ADDR_FAMILY_IPV4;
				/*
				 * Get subnet info.
				 */
				error = kvp_process_ip_address(
							     curp->अगरa_neपंचांगask,
							     AF_INET,
							     (अक्षर *)
							     ip_buffer->sub_net,
							     length,
							     &sn_offset);
				अगर (error)
					जाओ gather_ipaddr;
			पूर्ण अन्यथा अणु
				ip_buffer->addr_family |= ADDR_FAMILY_IPV6;

				/*
				 * Get subnet info in CIDR क्रमmat.
				 */
				weight = 0;
				sn_str = (अक्षर *)ip_buffer->sub_net;
				addr6 = (काष्ठा sockaddr_in6 *)
					curp->अगरa_neपंचांगask;
				w = addr6->sin6_addr.s6_addr32;

				क्रम (i = 0; i < 4; i++)
					weight += hweight32(&w[i]);

				प्र_लिखो(cidr_mask, "/%d", weight);
				अगर (length < sn_offset + म_माप(cidr_mask) + 1)
					जाओ gather_ipaddr;

				अगर (sn_offset == 0)
					म_नकल(sn_str, cidr_mask);
				अन्यथा अणु
					म_जोड़ो((अक्षर *)ip_buffer->sub_net, ";");
					म_जोड़ो(sn_str, cidr_mask);
				पूर्ण
				sn_offset += म_माप(sn_str) + 1;
			पूर्ण

			/*
			 * Collect other ip related configuration info.
			 */

			kvp_get_ipconfig_info(अगर_name, ip_buffer);
		पूर्ण

gather_ipaddr:
		error = kvp_process_ip_address(curp->अगरa_addr,
						curp->अगरa_addr->sa_family,
						buffer,
						length, &offset);
		अगर (error)
			जाओ getaddr_करोne;

		curp = curp->अगरa_next;
	पूर्ण

getaddr_करोne:
	मुक्तअगरaddrs(अगरap);
	वापस error;
पूर्ण

/*
 * Retrieve the IP given the MAC address.
 */
अटल पूर्णांक kvp_mac_to_ip(काष्ठा hv_kvp_ipaddr_value *kvp_ip_val)
अणु
	अक्षर *mac = (अक्षर *)kvp_ip_val->adapter_id;
	सूची *dir;
	काष्ठा dirent *entry;
	खाता    *file;
	अक्षर    *p, *x;
	अक्षर    *अगर_name = शून्य;
	अक्षर    buf[256];
	अक्षर dev_id[PATH_MAX];
	अचिन्हित पूर्णांक i;
	पूर्णांक error = HV_E_FAIL;

	dir = सूची_खोलो(KVP_NET_सूची);
	अगर (dir == शून्य)
		वापस HV_E_FAIL;

	जबतक ((entry = सूची_पढ़ो(dir)) != शून्य) अणु
		/*
		 * Set the state क्रम the next pass.
		 */
		snम_लिखो(dev_id, माप(dev_id), "%s%s/address", KVP_NET_सूची,
			 entry->d_name);

		file = ख_खोलो(dev_id, "r");
		अगर (file == शून्य)
			जारी;

		p = ख_माला_लो(buf, माप(buf), file);
		ख_बंद(file);
		अगर (!p)
			जारी;

		x = म_अक्षर(p, '\n');
		अगर (x)
			*x = '\0';

		क्रम (i = 0; i < म_माप(p); i++)
			p[i] = बड़े(p[i]);

		अगर (म_भेद(p, mac))
			जारी;

		/*
		 * Found the MAC match.
		 * A NIC (e.g. VF) matching the MAC, but without IP, is skipped.
		 */
		अगर_name = entry->d_name;
		अगर (!अगर_name)
			जारी;

		error = kvp_get_ip_info(0, अगर_name, KVP_OP_GET_IP_INFO,
					kvp_ip_val, MAX_IP_ADDR_SIZE * 2);

		अगर (!error && म_माप((अक्षर *)kvp_ip_val->ip_addr))
			अवरोध;
	पूर्ण

	बंद_सूची(dir);
	वापस error;
पूर्ण

अटल पूर्णांक expand_ipv6(अक्षर *addr, पूर्णांक type)
अणु
	पूर्णांक ret;
	काष्ठा in6_addr v6_addr;

	ret = inet_pton(AF_INET6, addr, &v6_addr);

	अगर (ret != 1) अणु
		अगर (type == NETMASK)
			वापस 1;
		वापस 0;
	पूर्ण

	प्र_लिखो(addr, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:"
		"%02x%02x:%02x%02x:%02x%02x",
		(पूर्णांक)v6_addr.s6_addr[0], (पूर्णांक)v6_addr.s6_addr[1],
		(पूर्णांक)v6_addr.s6_addr[2], (पूर्णांक)v6_addr.s6_addr[3],
		(पूर्णांक)v6_addr.s6_addr[4], (पूर्णांक)v6_addr.s6_addr[5],
		(पूर्णांक)v6_addr.s6_addr[6], (पूर्णांक)v6_addr.s6_addr[7],
		(पूर्णांक)v6_addr.s6_addr[8], (पूर्णांक)v6_addr.s6_addr[9],
		(पूर्णांक)v6_addr.s6_addr[10], (पूर्णांक)v6_addr.s6_addr[11],
		(पूर्णांक)v6_addr.s6_addr[12], (पूर्णांक)v6_addr.s6_addr[13],
		(पूर्णांक)v6_addr.s6_addr[14], (पूर्णांक)v6_addr.s6_addr[15]);

	वापस 1;

पूर्ण

अटल पूर्णांक is_ipv4(अक्षर *addr)
अणु
	पूर्णांक ret;
	काष्ठा in_addr ipv4_addr;

	ret = inet_pton(AF_INET, addr, &ipv4_addr);

	अगर (ret == 1)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_ip_val_buffer(अक्षर *in_buf, पूर्णांक *offset,
				अक्षर *out_buf, पूर्णांक out_len)
अणु
	अक्षर *x;
	अक्षर *start;

	/*
	 * in_buf has sequence of अक्षरacters that are separated by
	 * the अक्षरacter ';'. The last sequence करोes not have the
	 * terminating ";" अक्षरacter.
	 */
	start = in_buf + *offset;

	x = म_अक्षर(start, ';');
	अगर (x)
		*x = 0;
	अन्यथा
		x = start + म_माप(start);

	अगर (म_माप(start) != 0) अणु
		पूर्णांक i = 0;
		/*
		 * Get rid of leading spaces.
		 */
		जबतक (start[i] == ' ')
			i++;

		अगर ((x - start) <= out_len) अणु
			म_नकल(out_buf, (start + i));
			*offset += (x - start) + 1;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kvp_ग_लिखो_file(खाता *f, अक्षर *s1, अक्षर *s2, अक्षर *s3)
अणु
	पूर्णांक ret;

	ret = ख_लिखो(f, "%s%s%s%s\n", s1, s2, "=", s3);

	अगर (ret < 0)
		वापस HV_E_FAIL;

	वापस 0;
पूर्ण


अटल पूर्णांक process_ip_string(खाता *f, अक्षर *ip_string, पूर्णांक type)
अणु
	पूर्णांक error = 0;
	अक्षर addr[INET6_ADDRSTRLEN];
	पूर्णांक i = 0;
	पूर्णांक j = 0;
	अक्षर str[256];
	अक्षर sub_str[13];
	पूर्णांक offset = 0;

	स_रखो(addr, 0, माप(addr));

	जबतक (parse_ip_val_buffer(ip_string, &offset, addr,
					(MAX_IP_ADDR_SIZE * 2))) अणु

		sub_str[0] = 0;
		अगर (is_ipv4(addr)) अणु
			चयन (type) अणु
			हाल IPADDR:
				snम_लिखो(str, माप(str), "%s", "IPADDR");
				अवरोध;
			हाल NETMASK:
				snम_लिखो(str, माप(str), "%s", "NETMASK");
				अवरोध;
			हाल GATEWAY:
				snम_लिखो(str, माप(str), "%s", "GATEWAY");
				अवरोध;
			हाल DNS:
				snम_लिखो(str, माप(str), "%s", "DNS");
				अवरोध;
			पूर्ण

			अगर (type == DNS) अणु
				snम_लिखो(sub_str, माप(sub_str), "%d", ++i);
			पूर्ण अन्यथा अगर (type == GATEWAY && i == 0) अणु
				++i;
			पूर्ण अन्यथा अणु
				snम_लिखो(sub_str, माप(sub_str), "%d", i++);
			पूर्ण


		पूर्ण अन्यथा अगर (expand_ipv6(addr, type)) अणु
			चयन (type) अणु
			हाल IPADDR:
				snम_लिखो(str, माप(str), "%s", "IPV6ADDR");
				अवरोध;
			हाल NETMASK:
				snम_लिखो(str, माप(str), "%s", "IPV6NETMASK");
				अवरोध;
			हाल GATEWAY:
				snम_लिखो(str, माप(str), "%s",
					"IPV6_DEFAULTGW");
				अवरोध;
			हाल DNS:
				snम_लिखो(str, माप(str), "%s",  "DNS");
				अवरोध;
			पूर्ण

			अगर (type == DNS) अणु
				snम_लिखो(sub_str, माप(sub_str), "%d", ++i);
			पूर्ण अन्यथा अगर (j == 0) अणु
				++j;
			पूर्ण अन्यथा अणु
				snम_लिखो(sub_str, माप(sub_str), "_%d", j++);
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस  HV_INVALIDARG;
		पूर्ण

		error = kvp_ग_लिखो_file(f, str, sub_str, addr);
		अगर (error)
			वापस error;
		स_रखो(addr, 0, माप(addr));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvp_set_ip_info(अक्षर *अगर_name, काष्ठा hv_kvp_ipaddr_value *new_val)
अणु
	पूर्णांक error = 0;
	अक्षर अगर_file[PATH_MAX];
	खाता *file;
	अक्षर cmd[PATH_MAX];
	अक्षर *mac_addr;
	पूर्णांक str_len;

	/*
	 * Set the configuration क्रम the specअगरied पूर्णांकerface with
	 * the inक्रमmation provided. Since there is no standard
	 * way to configure an पूर्णांकerface, we will have an बाह्यal
	 * script that करोes the job of configuring the पूर्णांकerface and
	 * flushing the configuration.
	 *
	 * The parameters passed to this बाह्यal script are:
	 * 1. A configuration file that has the specअगरied configuration.
	 *
	 * We will embed the name of the पूर्णांकerface in the configuration
	 * file: अगरcfg-ethx (where ethx is the पूर्णांकerface name).
	 *
	 * The inक्रमmation provided here may be more than what is needed
	 * in a given distro to configure the पूर्णांकerface and so are मुक्त
	 * ignore inक्रमmation that may not be relevant.
	 *
	 * Here is the क्रमmat of the ip configuration file:
	 *
	 * HWADDR=macaddr
	 * DEVICE=पूर्णांकerface name
	 * BOOTPROTO=<protocol> (where <protocol> is "dhcp" अगर DHCP is configured
	 *                       or "none" अगर no boot-समय protocol should be used)
	 *
	 * IPADDR0=ipaddr1
	 * IPADDR1=ipaddr2
	 * IPADDRx=ipaddry (where y = x + 1)
	 *
	 * NETMASK0=neपंचांगask1
	 * NETMASKx=neपंचांगasky (where y = x + 1)
	 *
	 * GATEWAY=ipaddr1
	 * GATEWAYx=ipaddry (where y = x + 1)
	 *
	 * DNSx=ipaddrx (where first DNS address is tagged as DNS1 etc)
	 *
	 * IPV6 addresses will be tagged as IPV6ADDR, IPV6 gateway will be
	 * tagged as IPV6_DEFAULTGW and IPV6 NETMASK will be tagged as
	 * IPV6NETMASK.
	 *
	 * The host can specअगरy multiple ipv4 and ipv6 addresses to be
	 * configured क्रम the पूर्णांकerface. Furthermore, the configuration
	 * needs to be persistent. A subsequent GET call on the पूर्णांकerface
	 * is expected to वापस the configuration that is set via the SET
	 * call.
	 */

	snम_लिखो(अगर_file, माप(अगर_file), "%s%s%s", KVP_CONFIG_LOC,
		"/ifcfg-", अगर_name);

	file = ख_खोलो(अगर_file, "w");

	अगर (file == शून्य) अणु
		syslog(LOG_ERR, "Failed to open config file; error: %d %s",
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस HV_E_FAIL;
	पूर्ण

	/*
	 * First ग_लिखो out the MAC address.
	 */

	mac_addr = kvp_अगर_name_to_mac(अगर_name);
	अगर (mac_addr == शून्य) अणु
		error = HV_E_FAIL;
		जाओ setval_error;
	पूर्ण

	error = kvp_ग_लिखो_file(file, "HWADDR", "", mac_addr);
	मुक्त(mac_addr);
	अगर (error)
		जाओ setval_error;

	error = kvp_ग_लिखो_file(file, "DEVICE", "", अगर_name);
	अगर (error)
		जाओ setval_error;

	/*
	 * The dhcp_enabled flag is only क्रम IPv4. In the हाल the host only
	 * injects an IPv6 address, the flag is true, but we still need to
	 * proceed to parse and pass the IPv6 inक्रमmation to the
	 * disto-specअगरic script hv_set_अगरconfig.
	 */
	अगर (new_val->dhcp_enabled) अणु
		error = kvp_ग_लिखो_file(file, "BOOTPROTO", "", "dhcp");
		अगर (error)
			जाओ setval_error;

	पूर्ण अन्यथा अणु
		error = kvp_ग_लिखो_file(file, "BOOTPROTO", "", "none");
		अगर (error)
			जाओ setval_error;
	पूर्ण

	/*
	 * Write the configuration क्रम ipaddress, neपंचांगask, gateway and
	 * name servers.
	 */

	error = process_ip_string(file, (अक्षर *)new_val->ip_addr, IPADDR);
	अगर (error)
		जाओ setval_error;

	error = process_ip_string(file, (अक्षर *)new_val->sub_net, NETMASK);
	अगर (error)
		जाओ setval_error;

	error = process_ip_string(file, (अक्षर *)new_val->gate_way, GATEWAY);
	अगर (error)
		जाओ setval_error;

	error = process_ip_string(file, (अक्षर *)new_val->dns_addr, DNS);
	अगर (error)
		जाओ setval_error;

	ख_बंद(file);

	/*
	 * Now that we have populated the configuration file,
	 * invoke the बाह्यal script to करो its magic.
	 */

	str_len = snम_लिखो(cmd, माप(cmd), KVP_SCRIPTS_PATH "%s %s",
			   "hv_set_ifconfig", अगर_file);
	/*
	 * This is a little overcautious, but it's necessary to suppress some
	 * false warnings from gcc 8.0.1.
	 */
	अगर (str_len <= 0 || (अचिन्हित पूर्णांक)str_len >= माप(cmd)) अणु
		syslog(LOG_ERR, "Cmd '%s' (len=%d) may be too long",
		       cmd, str_len);
		वापस HV_E_FAIL;
	पूर्ण

	अगर (प्रणाली(cmd)) अणु
		syslog(LOG_ERR, "Failed to execute cmd '%s'; error: %d %s",
				cmd, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस HV_E_FAIL;
	पूर्ण
	वापस 0;

setval_error:
	syslog(LOG_ERR, "Failed to write config file");
	ख_बंद(file);
	वापस error;
पूर्ण


अटल व्योम
kvp_get_करोमुख्य_name(अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा addrinfo	hपूर्णांकs, *info ;
	पूर्णांक error = 0;

	gethostname(buffer, length);
	स_रखो(&hपूर्णांकs, 0, माप(hपूर्णांकs));
	hपूर्णांकs.ai_family = AF_INET; /*Get only ipv4 addrinfo. */
	hपूर्णांकs.ai_socktype = SOCK_STREAM;
	hपूर्णांकs.ai_flags = AI_CANONNAME;

	error = getaddrinfo(buffer, शून्य, &hपूर्णांकs, &info);
	अगर (error != 0) अणु
		snम_लिखो(buffer, length, "getaddrinfo failed: 0x%x %s",
			error, gai_म_त्रुटि(error));
		वापस;
	पूर्ण
	snम_लिखो(buffer, length, "%s", info->ai_canonname);
	मुक्तaddrinfo(info);
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
	पूर्णांक kvp_fd = -1, len;
	पूर्णांक error;
	काष्ठा pollfd pfd;
	अक्षर    *p;
	काष्ठा hv_kvp_msg hv_msg[1];
	अक्षर	*key_value;
	अक्षर	*key_name;
	पूर्णांक	op;
	पूर्णांक	pool;
	अक्षर	*अगर_name;
	काष्ठा hv_kvp_ipaddr_value *kvp_ip_val;
	पूर्णांक daemonize = 1, दीर्घ_index = 0, opt;

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

	खोलोlog("KVP", 0, LOG_USER);
	syslog(LOG_INFO, "KVP starting; pid is:%d", getpid());

	/*
	 * Retrieve OS release inक्रमmation.
	 */
	kvp_get_os_info();
	/*
	 * Cache Fully Qualअगरied Doमुख्य Name because getaddrinfo takes an
	 * unpredictable amount of समय to finish.
	 */
	kvp_get_करोमुख्य_name(full_करोमुख्य_name, माप(full_करोमुख्य_name));

	अगर (kvp_file_init()) अणु
		syslog(LOG_ERR, "Failed to initialize the pools");
		निकास(निकास_त्रुटि);
	पूर्ण

reखोलो_kvp_fd:
	अगर (kvp_fd != -1)
		बंद(kvp_fd);
	in_hand_shake = 1;
	kvp_fd = खोलो("/dev/vmbus/hv_kvp", O_RDWR | O_CLOEXEC);

	अगर (kvp_fd < 0) अणु
		syslog(LOG_ERR, "open /dev/vmbus/hv_kvp failed; error: %d %s",
		       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	/*
	 * Register ourselves with the kernel.
	 */
	hv_msg->kvp_hdr.operation = KVP_OP_REGISTER1;
	len = ग_लिखो(kvp_fd, hv_msg, माप(काष्ठा hv_kvp_msg));
	अगर (len != माप(काष्ठा hv_kvp_msg)) अणु
		syslog(LOG_ERR, "registration to kernel failed; error: %d %s",
		       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		बंद(kvp_fd);
		निकास(निकास_त्रुटि);
	पूर्ण

	pfd.fd = kvp_fd;

	जबतक (1) अणु
		pfd.events = POLLIN;
		pfd.revents = 0;

		अगर (poll(&pfd, 1, -1) < 0) अणु
			syslog(LOG_ERR, "poll failed; error: %d %s", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			अगर (त्रुटि_सं == EINVAL) अणु
				बंद(kvp_fd);
				निकास(निकास_त्रुटि);
			पूर्ण
			अन्यथा
				जारी;
		पूर्ण

		len = पढ़ो(kvp_fd, hv_msg, माप(काष्ठा hv_kvp_msg));

		अगर (len != माप(काष्ठा hv_kvp_msg)) अणु
			syslog(LOG_ERR, "read failed; error:%d %s",
			       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_kvp_fd;
		पूर्ण

		/*
		 * We will use the KVP header inक्रमmation to pass back
		 * the error from this daemon. So, first copy the state
		 * and set the error code to success.
		 */
		op = hv_msg->kvp_hdr.operation;
		pool = hv_msg->kvp_hdr.pool;
		hv_msg->error = HV_S_OK;

		अगर ((in_hand_shake) && (op == KVP_OP_REGISTER1)) अणु
			/*
			 * Driver is रेजिस्टरing with us; stash away the version
			 * inक्रमmation.
			 */
			in_hand_shake = 0;
			p = (अक्षर *)hv_msg->body.kvp_रेजिस्टर.version;
			lic_version = दो_स्मृति(म_माप(p) + 1);
			अगर (lic_version) अणु
				म_नकल(lic_version, p);
				syslog(LOG_INFO, "KVP LIC Version: %s",
				       lic_version);
			पूर्ण अन्यथा अणु
				syslog(LOG_ERR, "malloc failed");
			पूर्ण
			जारी;
		पूर्ण

		चयन (op) अणु
		हाल KVP_OP_GET_IP_INFO:
			kvp_ip_val = &hv_msg->body.kvp_ip_val;

			error = kvp_mac_to_ip(kvp_ip_val);

			अगर (error)
				hv_msg->error = error;

			अवरोध;

		हाल KVP_OP_SET_IP_INFO:
			kvp_ip_val = &hv_msg->body.kvp_ip_val;
			अगर_name = kvp_get_अगर_name(
					(अक्षर *)kvp_ip_val->adapter_id);
			अगर (अगर_name == शून्य) अणु
				/*
				 * We could not map the guid to an
				 * पूर्णांकerface name; वापस error.
				 */
				hv_msg->error = HV_GUID_NOTFOUND;
				अवरोध;
			पूर्ण
			error = kvp_set_ip_info(अगर_name, kvp_ip_val);
			अगर (error)
				hv_msg->error = error;

			मुक्त(अगर_name);
			अवरोध;

		हाल KVP_OP_SET:
			अगर (kvp_key_add_or_modअगरy(pool,
					hv_msg->body.kvp_set.data.key,
					hv_msg->body.kvp_set.data.key_size,
					hv_msg->body.kvp_set.data.value,
					hv_msg->body.kvp_set.data.value_size))
					hv_msg->error = HV_S_CONT;
			अवरोध;

		हाल KVP_OP_GET:
			अगर (kvp_get_value(pool,
					hv_msg->body.kvp_set.data.key,
					hv_msg->body.kvp_set.data.key_size,
					hv_msg->body.kvp_set.data.value,
					hv_msg->body.kvp_set.data.value_size))
					hv_msg->error = HV_S_CONT;
			अवरोध;

		हाल KVP_OP_DELETE:
			अगर (kvp_key_delete(pool,
					hv_msg->body.kvp_delete.key,
					hv_msg->body.kvp_delete.key_size))
					hv_msg->error = HV_S_CONT;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (op != KVP_OP_ENUMERATE)
			जाओ kvp_करोne;

		/*
		 * If the pool is KVP_POOL_AUTO, dynamically generate
		 * both the key and the value; अगर not पढ़ो from the
		 * appropriate pool.
		 */
		अगर (pool != KVP_POOL_AUTO) अणु
			अगर (kvp_pool_क्रमागतerate(pool,
					hv_msg->body.kvp_क्रमागत_data.index,
					hv_msg->body.kvp_क्रमागत_data.data.key,
					HV_KVP_EXCHANGE_MAX_KEY_SIZE,
					hv_msg->body.kvp_क्रमागत_data.data.value,
					HV_KVP_EXCHANGE_MAX_VALUE_SIZE))
					hv_msg->error = HV_S_CONT;
			जाओ kvp_करोne;
		पूर्ण

		key_name = (अक्षर *)hv_msg->body.kvp_क्रमागत_data.data.key;
		key_value = (अक्षर *)hv_msg->body.kvp_क्रमागत_data.data.value;

		चयन (hv_msg->body.kvp_क्रमागत_data.index) अणु
		हाल FullyQualअगरiedDoमुख्यName:
			म_नकल(key_value, full_करोमुख्य_name);
			म_नकल(key_name, "FullyQualifiedDomainName");
			अवरोध;
		हाल IntegrationServicesVersion:
			म_नकल(key_name, "IntegrationServicesVersion");
			म_नकल(key_value, lic_version);
			अवरोध;
		हाल NetworkAddressIPv4:
			kvp_get_ip_info(AF_INET, शून्य, KVP_OP_ENUMERATE,
				key_value, HV_KVP_EXCHANGE_MAX_VALUE_SIZE);
			म_नकल(key_name, "NetworkAddressIPv4");
			अवरोध;
		हाल NetworkAddressIPv6:
			kvp_get_ip_info(AF_INET6, शून्य, KVP_OP_ENUMERATE,
				key_value, HV_KVP_EXCHANGE_MAX_VALUE_SIZE);
			म_नकल(key_name, "NetworkAddressIPv6");
			अवरोध;
		हाल OSBuildNumber:
			म_नकल(key_value, os_build);
			म_नकल(key_name, "OSBuildNumber");
			अवरोध;
		हाल OSName:
			म_नकल(key_value, os_name);
			म_नकल(key_name, "OSName");
			अवरोध;
		हाल OSMajorVersion:
			म_नकल(key_value, os_major);
			म_नकल(key_name, "OSMajorVersion");
			अवरोध;
		हाल OSMinorVersion:
			म_नकल(key_value, os_minor);
			म_नकल(key_name, "OSMinorVersion");
			अवरोध;
		हाल OSVersion:
			म_नकल(key_value, os_version);
			म_नकल(key_name, "OSVersion");
			अवरोध;
		हाल ProcessorArchitecture:
			म_नकल(key_value, processor_arch);
			म_नकल(key_name, "ProcessorArchitecture");
			अवरोध;
		शेष:
			hv_msg->error = HV_S_CONT;
			अवरोध;
		पूर्ण

		/*
		 * Send the value back to the kernel. Note: the ग_लिखो() may
		 * वापस an error due to hibernation; we can ignore the error
		 * by resetting the dev file, i.e. closing and re-खोलोing it.
		 */
kvp_करोne:
		len = ग_लिखो(kvp_fd, hv_msg, माप(काष्ठा hv_kvp_msg));
		अगर (len != माप(काष्ठा hv_kvp_msg)) अणु
			syslog(LOG_ERR, "write failed; error: %d %s", त्रुटि_सं,
			       म_त्रुटि(त्रुटि_सं));
			जाओ reखोलो_kvp_fd;
		पूर्ण
	पूर्ण

	बंद(kvp_fd);
	निकास(0);
पूर्ण
