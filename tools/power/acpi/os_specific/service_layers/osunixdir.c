<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: osunixdir - Unix directory access पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <dirent.h>
#समावेश <fnmatch.h>
#समावेश <प्रकार.स>
#समावेश <sys/स्थिति.स>

/*
 * Allocated काष्ठाure वापसed from os_खोलो_directory
 */
प्रकार काष्ठा बाह्यal_find_info अणु
	अक्षर *dir_pathname;
	सूची *dir_ptr;
	अक्षर temp_buffer[256];
	अक्षर *wildcard_spec;
	अक्षर requested_file_type;

पूर्ण बाह्यal_find_info;

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_खोलो_directory
 *
 * PARAMETERS:  dir_pathname        - Full pathname to the directory
 *              wildcard_spec       - string of the क्रमm "*.c", etc.
 *
 * RETURN:      A directory "handle" to be used in subsequent search operations.
 *              शून्य वापसed on failure.
 *
 * DESCRIPTION: Open a directory in preparation क्रम a wildcard search
 *
 ******************************************************************************/

व्योम *acpi_os_खोलो_directory(अक्षर *dir_pathname,
			     अक्षर *wildcard_spec, अक्षर requested_file_type)
अणु
	काष्ठा बाह्यal_find_info *बाह्यal_info;
	सूची *dir;

	/* Allocate the info काष्ठा that will be वापसed to the caller */

	बाह्यal_info = सुस्मृति(1, माप(काष्ठा बाह्यal_find_info));
	अगर (!बाह्यal_info) अणु
		वापस (शून्य);
	पूर्ण

	/* Get the directory stream */

	dir = सूची_खोलो(dir_pathname);
	अगर (!dir) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot open directory - %s\n", dir_pathname);
		मुक्त(बाह्यal_info);
		वापस (शून्य);
	पूर्ण

	/* Save the info in the वापस काष्ठाure */

	बाह्यal_info->wildcard_spec = wildcard_spec;
	बाह्यal_info->requested_file_type = requested_file_type;
	बाह्यal_info->dir_pathname = dir_pathname;
	बाह्यal_info->dir_ptr = dir;
	वापस (बाह्यal_info);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_get_next_filename
 *
 * PARAMETERS:  dir_handle          - Created via acpi_os_खोलो_directory
 *
 * RETURN:      Next filename matched. शून्य अगर no more matches.
 *
 * DESCRIPTION: Get the next file in the directory that matches the wildcard
 *              specअगरication.
 *
 ******************************************************************************/

अक्षर *acpi_os_get_next_filename(व्योम *dir_handle)
अणु
	काष्ठा बाह्यal_find_info *बाह्यal_info = dir_handle;
	काष्ठा dirent *dir_entry;
	अक्षर *temp_str;
	पूर्णांक str_len;
	काष्ठा stat temp_stat;
	पूर्णांक err;

	जबतक ((dir_entry = सूची_पढ़ो(बाह्यal_info->dir_ptr))) अणु
		अगर (!fnmatch
		    (बाह्यal_info->wildcard_spec, dir_entry->d_name, 0)) अणु
			अगर (dir_entry->d_name[0] == '.') अणु
				जारी;
			पूर्ण

			str_len = म_माप(dir_entry->d_name) +
			    म_माप(बाह्यal_info->dir_pathname) + 2;

			temp_str = सुस्मृति(str_len, 1);
			अगर (!temp_str) अणु
				ख_लिखो(मानक_त्रुटि,
					"Could not allocate buffer for temporary string\n");
				वापस (शून्य);
			पूर्ण

			म_नकल(temp_str, बाह्यal_info->dir_pathname);
			म_जोड़ो(temp_str, "/");
			म_जोड़ो(temp_str, dir_entry->d_name);

			err = stat(temp_str, &temp_stat);
			अगर (err == -1) अणु
				ख_लिखो(मानक_त्रुटि,
					"Cannot stat file (should not happen) - %s\n",
					temp_str);
				मुक्त(temp_str);
				वापस (शून्य);
			पूर्ण

			मुक्त(temp_str);

			अगर ((S_ISसूची(temp_stat.st_mode)
			     && (बाह्यal_info->requested_file_type ==
				 REQUEST_सूची_ONLY))
			    || ((!S_ISसूची(temp_stat.st_mode)
				 && बाह्यal_info->requested_file_type ==
				 REQUEST_खाता_ONLY))) अणु

				/* copy to a temp buffer because dir_entry काष्ठा is on the stack */

				म_नकल(बाह्यal_info->temp_buffer,
				       dir_entry->d_name);
				वापस (बाह्यal_info->temp_buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_बंद_directory
 *
 * PARAMETERS:  dir_handle          - Created via acpi_os_खोलो_directory
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Close the खोलो directory and cleanup.
 *
 ******************************************************************************/

व्योम acpi_os_बंद_directory(व्योम *dir_handle)
अणु
	काष्ठा बाह्यal_find_info *बाह्यal_info = dir_handle;

	/* Close the directory and मुक्त allocations */

	बंद_सूची(बाह्यal_info->dir_ptr);
	मुक्त(dir_handle);
पूर्ण
