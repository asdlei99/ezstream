#include <check.h>

#include "cfg_private.h"
#include "log.h"

Suite * cfg_xmlfile_suite(void);
void	setup_checked(void);
void	teardown_checked(void);

START_TEST(test_reload)
{
	ck_assert_int_eq(cfg_set_program_config_file(EXAMPLESDIR "/ezstream-file_template.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_set_program_config_file(EXAMPLESDIR "/ezstream-full.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_set_program_config_file(EXAMPLESDIR "/ezstream-minimal.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_set_program_config_file(EXAMPLESDIR "/ezstream-stdin.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_set_program_config_file(EXAMPLESDIR "/ezstream-video.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_file_reload(), 0);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad2.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad3.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad4.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad5.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
	ck_assert_int_eq(cfg_set_program_config_file(SRCDIR "/config-bad6.xml",
	    NULL), 0);
	ck_assert_int_eq(cfg_file_reload(), -1);
}
END_TEST

Suite *
cfg_xmlfile_suite(void)
{
	Suite	*s;
	TCase	*tc_xmlcfg;

	s = suite_create("Config");

	tc_xmlcfg = tcase_create("XmlConfigFile");
	tcase_add_checked_fixture(tc_xmlcfg, setup_checked, teardown_checked);
	tcase_add_test(tc_xmlcfg, test_reload);
	suite_add_tcase(s, tc_xmlcfg);

	return (s);
}

void
setup_checked(void)
{
	if (0 < cfg_init() ||
	    0 < cfg_set_program_name("check_cfg_xmlfile", NULL) ||
	    0 < log_init(cfg_get_program_name()))
		ck_abort_msg("setup_checked failed");
}

void
teardown_checked(void)
{
	log_exit();
	cfg_exit();
}

int
main(void)
{
	int	 num_failed;
	Suite	*s;
	SRunner	*sr;

	s = cfg_xmlfile_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	num_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	if (num_failed)
		return (1);
	return (0);
}
