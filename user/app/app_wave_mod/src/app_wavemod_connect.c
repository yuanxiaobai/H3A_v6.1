/*********************************************************************************************
*            �麣�����������޹�˾
*            http://www.zhkh.com
* ģ������: wave ����ģ��������Ӳ�
* ����ʱ��:2010-09-19
* ������˾ :����
* �ļ�����:app_wavemod_connect.c
* ������ :�ҳ�
* ��������:ʵ�ָ�ģ��Ķ�������
*-------------------------------------------------------------------*/
#include"app_wavemod_inside.h"
#include "../../../support\app_support.h"

/********************************************************************
 * @������ :�ҳ�
 * @���� : ϵͳ����ģ����Դ��ʼ��
 *
 * @���� :NONE
 *
 *@���  :NONE
********************************************************************/
void app_wavemod_resource_init( void )
{
	app_module_color_select(2);
	return;
}
/********************************************************************
 * @������ :�ҳ�
 * @���� : ģ��������
 *
 * @���� :NONE
 *
 *@���  :NONE
********************************************************************/
void app_wavemod_insmod( void )
{
	app_global_resouce_req( 0 );  /*����ռ�ù�����Դ*/
	app_wavemod_resource_init();/*��ʼ����ģ����Դ*/
	app_wavemod_fun_entry();    /*��ģ�����������*/
	DBGMSG( "wavemod....\n", LOG_NP, LOG_NP );
	return;
}
/********************************************************************
 * @������ :�ҳ�
 * @���� : ģ��ж�����
 *
 * @���� :NONE
 *
 *@���  :NONE
********************************************************************/
void app_wavemod_exit( void )
{
	app_global_resouce_release( 0 );          /*�ͷ�ռ�ù�����Դ*/
	app_wavemod_fun_exit();/*�˳���ģ��������*/
	DBGMSG( "wavemod=>", LOG_NP, LOG_NP );
	return;
}
/********************************************************************
 * @������ :�ҳ�
 * @���� : ��ģ��ӵ������б�
 *
 * @���� :NONE
 *
 *@���  :NONE
********************************************************************/
Bsize_t app_wavemod_add( void )
{
	app_mod_inlet_t temp;
	Bsize_t mod_id;
	temp.insmod_fun = app_wavemod_insmod;/*ģ�����*/
	temp.exitmod_fun = app_wavemod_exit;/*ģ�����*/
	mod_id = app_module_add( &temp );
	return mod_id;
}
/*module AUTO Register*/
#pragma DATA_SECTION (app_wavemod_list,"MOD_LIST_ADDR")
const mod_member_t app_wavemod_list[]=
{
	app_wavemod_add,
	"WAVE",
	0x5a5a
};
