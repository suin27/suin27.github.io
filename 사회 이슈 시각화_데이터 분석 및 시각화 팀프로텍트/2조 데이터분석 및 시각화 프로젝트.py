import urllib.parse
from urllib.request import urlopen
import pandas as pd
from bs4 import BeautifulSoup
from matplotlib import pyplot as plt
import urllib.request
import seaborn as sns
import numpy as np
from matplotlib import font_manager, rc
from openpyxl.workbook import Workbook
import geopandas as gpd
import json
from matplotlib.pyplot import sci, figure
from numpy.random import randn
import matplotlib.ticker as mticker

import re
import xlsxwriter
from pandas import DataFrame
from matplotlib import pyplot as plt
import seaborn as sns
import pandas as pd
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By

pd.set_option('mode.chained_assignment', None)

itemList=[]

sn = 0
wn = 1
pltkorea = plt



def koreanFont():
    plt.rc('font',family='NanumGothic')
    plt.rcParams['axes.unicode_minus']=False

def URLGetDataGet(year, month):
    ym=str(year)+format(month,'02')
    baseURL='http://apis.data.go.kr/1741000/stdgSexdBrthReg/selectStdgSexdBrthReg?serviceKey=Sw3ZLK8YVkQ0zCikPBGPFU0LwYML0zotUApCyeoylhPAXkyrHcI7OJP4I3%2BNyMyyBH6yK4NRBwOOdGMJ9e5Rhg%3D%3D'
    param=f'&stdgCd=1100000000&srchFrYm={urllib.parse.quote(ym)}&srchToYm={urllib.parse.quote(ym)}&lv=1&type=XML&numOfRows=10&pageNo=1'
    URL=baseURL+param
    try:
        resXml=urlopen(URL)
        resData=resXml.read()
        soup=BeautifulSoup(resData,'lxml-xml')
        items=soup.find_all('item')
        global itemList
        for i in items:
            yearMonth=format(int(i.find('statsYm').text.strip()),'06')
            area=i.find('ctpvNm').text.strip()
            total=int(i.find('totNmprCnt').text.strip())
            male=int(i.find('maleNmprCnt').text.strip())
            female=int(i.find('femlNmprCnt').text.strip())
            dic={'통계년월':yearMonth,'시군구명':area, '총인구수':total,'남자인구수':male,'여자인구수':female}
            itemList.append(dic)
    except Exception as ex:
        print('연결 에러',ex)

def excelWriter(df,df2,df1_,df2_,dataCsv):
    writer = pd.ExcelWriter('df.xlsx',
                            engine='xlsxwriter')
    df.to_excel(writer, sheet_name='Sheet1')
    writer.close()
    writer = pd.ExcelWriter('df2.xlsx',
                            engine='xlsxwriter')
    df2.to_excel(writer, sheet_name='Sheet1')
    writer.close()
    writer = pd.ExcelWriter('df1_.xlsx',
                            engine='xlsxwriter')
    df1_.to_excel(writer, sheet_name='Sheet1')
    writer.close()
    writer = pd.ExcelWriter('df2_.xlsx',
                            engine='xlsxwriter')
    df2_.to_excel(writer, sheet_name='Sheet1')
    writer.close()
    writer = pd.ExcelWriter('dataCsv.xlsx',
                            engine='xlsxwriter')
    dataCsv.to_excel(writer, sheet_name='Sheet1')
    writer.close()
    print('excel 파일 5개 저장 완료')

def baby():
    URLGetDataGet(2022, 10)
    URLGetDataGet(2022, 11)
    URLGetDataGet(2022, 12)
    URLGetDataGet(2023, 1)
    df = pd.DataFrame.from_dict(itemList)

    df1 = df.loc[:, ['시군구명', '총인구수', '남자인구수', '여자인구수']]
    df1.index = df.통계년월
    df2 = df.loc[:, ['통계년월', '총인구수', '남자인구수', '여자인구수']]
    df2.index = df.시군구명
    dic1 = {'202210': df1.loc['202210'].sum(axis=0)[1:], '202211': df1.loc['202211'].sum(axis=0)[1:],
            '202212': df1.loc['202212'].sum(axis=0)[1:], '202301': df1.loc['202301'].sum(axis=0)[1:]}
    dic2 = {'서울특별시': df2.loc['서울특별시'].sum(axis=0)[1:], '부산광역시': df2.loc['부산광역시'].sum(axis=0)[1:],
            '대구광역시': df2.loc['대구광역시'].sum(axis=0)[1:],
            '인천광역시': df2.loc['인천광역시'].sum(axis=0)[1:], '광주광역시': df2.loc['광주광역시'].sum(axis=0)[1:],
            '대전광역시': df2.loc['대전광역시'].sum(axis=0)[1:],
            '울산광역시': df2.loc['울산광역시'].sum(axis=0)[1:], '세종특별자치시': df2.loc['세종특별자치시'].sum(axis=0)[1:],
            '경기도': df2.loc['경기도'].sum(axis=0)[1:],
            '강원도': df2.loc['강원도'].sum(axis=0)[1:]}
    df1_ = pd.DataFrame.from_dict(dic1)
    df2_ = pd.DataFrame.from_dict(dic2)

    dataCsv = pd.read_csv('출생아 수 합계 출산율 자연 증가.csv', sep=',', encoding='cp949')
    dataCsv1 = pd.read_csv('출생아 수 합계 출산율 자연 증가.csv', sep=',', encoding='cp949', index_col=0)
    dataCsv2 = pd.read_csv('출생아 수 합계 출산율 자연 증가.csv', sep=',', encoding='cp949', index_col=0)

    sns.set_style('whitegrid')
    koreanFont()

    grid = plt.GridSpec(2, 2)
    ax1 = plt.subplot(grid[0, 0])
    ax2 = plt.subplot(grid[0, 1])
    ax3 = plt.subplot(grid[1, 0:])

    sns.lineplot(data=df[df.시군구명 == '경기도'], x='통계년월', y='총인구수', color='DarkOrange', linestyle=':', marker='o', ax=ax1)
    ax1.set_title('경기도 월별 출생 등록자 수', loc='center', pad=13)
    ax1.set_ylabel('총인구수', rotation=0, labelpad=33)

    sns.boxplot(data=df, x='통계년월', y='총인구수', palette='Set2', ax=ax2)
    ax2.set_title('법정동별 성별 출생 등록자 수', loc='center', pad=13)
    ax2.set_ylabel('총인구수', rotation=0, labelpad=33)

    sns.barplot(x='통계년월', y='총인구수', data=df, hue='시군구명', palette='Accent', ax=ax3)
    ax3.set_title('법정동별 성별 출생 등록자 수', loc='center', pad=13)
    ax3.set_ylabel('총인구수', rotation=0, labelpad=33)
    ax3.legend(loc='upper left')
    plt.show()

    df.index = df.통계년월
    df = df.loc[:, ['시군구명', '총인구수', '남자인구수', '여자인구수']]
    sns.pairplot(df, hue='시군구명', palette='husl', markers=['o', 's', 'd', 'D', '*', 'h', 'v', 'X', '<', '>'],
                 vars=['남자인구수', '여자인구수'], plot_kws={'alpha': 0.8})
    plt.yticks(rotation=0, fontsize=12)
    plt.xticks(fontsize=12)
    plt.grid(True)
    plt.show()

    sns.pairplot(dataCsv, hue='기본항목별')
    plt.show()

    # Violin plot +  Strip plot
    dataCsv2 = dataCsv2.transpose()
    dataCsv2.loc['2022', :] = 0
    dataCsv2.iloc[4, 0] = (df1_.loc['총인구수'].sum()) * 3
    sns.violinplot(x=dataCsv2.index, y='출생아수(명)', data=dataCsv2, color='LightBlue')
    sns.stripplot(x=dataCsv2.index, y='출생아수(명)', data=dataCsv2, hue='조출생률(천명당)', jitter=True, palette='RdPu')
    plt.title('지금 53살, 초등학교 1,2,3학년, 1살의 출생아수(명)', loc='center', pad=30, fontsize=18, fontweight='bold')
    plt.ylabel('출생아수(명)', rotation=0, labelpad=40, fontsize=12)
    plt.xticks(fontsize=12)
    plt.show()

    excelWriter(df,df2,df1_,df2_,dataCsv)

def drawKorea(targetData, blockedMap, d1, d2, cmapname):
    global wn
    global sn
    global pltkorea
    pltkorea.suptitle('지도로 보는 고령화문제   ', fontsize=24)
    pltkorea.subplot(1, 2, wn)
    pltkorea.subplot(1, 2, wn).set_title(f'{targetData}', fontsize=16)
    pltkorea.rcParams["figure.figsize"] = (18, 10)
    whitelabelmin = (max(blockedMap[targetData]) - min(blockedMap[targetData])) * 0.25 + \
                    min(blockedMap[targetData])
    datalabel = targetData
    vmin = min(blockedMap[targetData])
    vmax = max(blockedMap[targetData])
    BORED_LINES = [
        # 인천
        [(3, 2), (5, 2), (5, 3), (9, 3), (9, 1)],
        # 서울
        [(2, 5), (3, 5), (3, 4), (8, 4), (8, 7), (7, 7), (7, 9), (4, 9), (4, 7), (1, 7)],
        # 경기도
        [(1, 6), (1, 9), (3, 9), (3, 10), (8, 10), (8, 9), (9, 9), (9, 8), (10, 8), (10, 5), (9, 5), (9, 3)],
        # 강원도
        [(9, 12), (9, 10), (8, 10)],
        # 충청남도
        [(10, 5), (11, 5), (11, 4), (12, 4), (12, 5), (13, 5), (13, 4), (14, 4), (14, 2)],
        # 충청북도
        [(11, 5), (12, 5), (12, 6), (15, 6), (15, 7), (13, 7), (13, 8), (11, 8), (11, 9), (10, 9), (10, 8)],
        # 대전
        [(14, 4), (15, 4), (15, 6)],
        # 경상북도
        [(14, 7), (14, 9), (13, 9), (13, 11), (13, 13)],
        # 대구
        [(14, 8), (16, 8), (16, 10), (15, 10), (15, 11), (14, 11), (14, 12), (13, 12)],
        # 울산
        [(15, 11), (16, 11), (16, 13)],
        # 전라북도
        [(17, 1), (17, 3), (18, 3), (18, 6), (15, 6)],
        # 광주
        [(19, 2), (19, 4), (21, 4), (21, 3), (22, 3), (22, 2), (19, 2)],
        # 전라남도
        [(18, 5), (20, 5), (20, 6)],
        # 부산
        [(16, 9), (18, 9), (18, 8), (19, 8), (19, 9), (20, 9), (20, 10)]
    ]
    mapdata = blockedMap.pivot(index='y', columns='x', values=targetData)
    masked_mapdata = np.ma.masked_where(np.isnan(mapdata), mapdata)
    pltkorea.pcolor(masked_mapdata, vmin=vmin, vmax=vmax, cmap=cmapname,
                    edgecolor='#aaaaaa', linewidth=0.5)
    # 지역명 표시
    for idx, row in blockedMap.iterrows():
        annocolor = 'white' if row[targetData] > whitelabelmin else 'black'
        dispname = '{}\n{}'.format(row[d1][:2], row[d2][:-1])
        print(dispname)
        # 광역시는 구 이름이 겹치는 경우사 많으므로 시단위 이름도 같이 표현함.
        if row[d1].endswith('시') and not row[d1].startswith('세종'):
            if len(row[d2]) <= 2:
                dispname += row[d2][-1]
            else:
                dispname = row[d2][:-1]
        # 서대문구, 서귀포시와 같이 이름이 3자이상인경우 작은 글자로 표시함.
        if len(dispname.splitlines()[-1]) >= 3:
            fontsize, linespacing = 9.5, 1.5
        else:
            fontsize, linespacing = 11, 1.2
        pltkorea.annotate(dispname, (row['x'] + 0.5, row['y'] + 0.5), weight='bold',
                          fontsize=fontsize, ha='center', va='center', color=annocolor,
                          linespacing=linespacing)
    for path in BORED_LINES:
        ys, xs = zip(*path)
        pltkorea.plot(xs, ys, c='black', lw=4)
    pltkorea.gca().invert_yaxis()
    pltkorea.axis('off')
    cb = pltkorea.colorbar(shrink=.1, aspect=10)
    cb.set_label(datalabel)
    sn += 1
    wn += 1

    if sn == 2:
        pltkorea.tight_layout()
        pltkorea.show()
        sn = 0
        wn = 1
        # pltkorea.clf()
        pltkorea.close()


def make_map(datac):
    pltkorea.close()
    print('--------------')
    kr_sido = gpd.read_file('TL_SCCO_CTPRVN', encoding='cp949')
    kr_sido.head()
    print(kr_sido)
    print(type(kr_sido))
    print(datac)
    kr_sido.to_excel('팔도지도.xlsx')
    kr_sido.rename(columns={"CTP_KOR_NM": "행정구역별(1)"}, inplace=True)
    kr_sido = kr_sido.merge(datac, on='행정구역별(1)')
    kr_sido.drop(columns={"CTP_ENG_NM", "CTPRVN_CD"}, inplace=True)
    print(kr_sido)
    # 두 데이터를 머지로 통해 통합할수 있다. 열및 조건 일치시.
    fig, ax = plt.subplots(ncols=2, sharey=True, figsize=(16, 10))
    kr_sido.plot(ax=ax[0], column="고령인구비율_23", cmap="OrRd", legend=False, alpha=1)
    kr_sido.plot(ax=ax[1], column="고령인구비율_8", cmap="OrRd", legend=False, alpha=1)  # camp="OrRd",
    patch_col = ax[0].collections[0]
    patch_col2 = ax[1].collections[0]
    cb = fig.colorbar(patch_col, ax=ax[0], shrink=0.5)
    cb.set_label('비율')
    cb2 = fig.colorbar(patch_col2, ax=ax[1], shrink=0.5)
    cb2.set_label('비율')
    ax[0].set_title('23년도 고령인구비율', fontsize=16)
    ax[1].set_title('08년도 고령인구비율', fontsize=16)
    plt.suptitle('도별로 살펴보는 고령화', fontsize=24)
    plt.tight_layout()
    plt.show()
    ax[0].set_axis_off();
    ax[1].set_axis_off();


def make_bar(data_bar):

    data_bar_int = []
    barcheck = 0
    for i in data_bar.loc[0]:
        if barcheck == 0:
            pass
        else:
            data_bar_int.append(int(i))
        barcheck += 1
    pltold = plt
    pltold.figure(figsize=(18, 10))

    x = ['2008', '2009', '2010', '2011', '2012',
         '2013', '2014', '2015', '2016', '2017',
         '2018', '2019', '2020', '2021', '2022', '2023']
    y = data_bar_int
    bar = pltold.bar(x, y, color='green')

    pltold.xlabel('년도별 노인수', fontsize=13)
    pltold.ylabel('단위(백만명)    ', fontsize=13, rotation='horizontal', loc='top')
    pltold.title('대한민국 노인들은 얼마나 빠르게 늘고 있는가', fontsize=16)
    pltold.plot(label='People')
    for rect in bar:
        height = rect.get_height()
        pltold.text(rect.get_x() + rect.get_width() / 2.0, height, '%d' % height, ha='center', va='bottom', size=12)

    pltold.ylim(3000000)
    pltold.show()

def oldman():
    koreanFont()
    data_draw_korea = pd.read_csv('data_draw_korea.csv', index_col=0, encoding='utf-8')
    data_oldman_korea = pd.read_csv('data_old_korea.csv', encoding='cp949')
    data_oldold = pd.read_csv('data_old_old_korea.csv', encoding='cp949')
    exdf = pd.DataFrame()
    n = 0
    # 노인수23년도
    writer = pd.ExcelWriter('고령화정보.xlsx', engine='xlsxwriter')
    for n in range(0, 229):
        data_draw_korea.loc[n, '23년도65세이상인구'] = data_oldman_korea.loc[n, '65세이상인구']
    drawKorea('23년도65세이상인구', data_draw_korea, '광역시도', '행정구역', 'Blues')
    print(data_draw_korea)
    exdf1 = pd.concat([data_draw_korea[['인구수', '23년도65세이상인구', 'shortName']]])
    exdf1.to_excel(writer, sheet_name='sheet1')
    # 노인수08년도
    for n in range(0, 229):
        data_draw_korea.loc[n, '08년도65세이상인구'] = data_oldold.loc[n, '65세이상인구']
    drawKorea('08년도65세이상인구', data_draw_korea, '광역시도', '행정구역', 'Blues')
    exdf2 = pd.concat([data_draw_korea[['인구수', '08년도65세이상인구', 'shortName']]])
    exdf2.to_excel(writer, sheet_name='sheet2')
    # 전체 인구 대비 노인 비율23년도
    for n in range(0, 229):
        data_draw_korea.loc[n, '23년도고령인구비율'] = data_oldman_korea.loc[n, '고령인구비율']
    drawKorea('23년도고령인구비율', data_draw_korea, '광역시도', '행정구역', 'Reds')
    exdf3 = pd.concat([data_draw_korea[['인구수', '23년도고령인구비율', 'shortName']]])
    exdf3.to_excel(writer, sheet_name='sheet3')
    # 전체 인구 대비 노인 비율08년도
    for n in range(0, 229):
        data_draw_korea.loc[n, '08년도고령인구비율'] = data_oldold.loc[n, '고령인구비율']
    drawKorea('08년도고령인구비율', data_draw_korea, '광역시도', '행정구역', 'Reds')
    exdf4 = pd.concat([data_draw_korea[['인구수', '08년도고령인구비율', 'shortName']]])
    exdf4.to_excel(writer, sheet_name='sheet4')
    # 도 기준으로 지도 시각화
    data_chart = pd.read_csv('data_old_chart.csv', encoding='cp949')
    for i in range(0, 17):
        if data_chart['고령인구비율_8'][i] == '-':
            data_chart['고령인구비율_8'][i] = 0
        if data_chart['65세이상인구_8'][i] == '-':
            data_chart['65세이상인구_8'][i] = 0
        if data_chart['전체인구_8'][i] == '-':
            data_chart['전체인구_8'][i] = 0
    make_map(data_chart)
    # 년도별 노인인구수 증가 막대그래프
    data_bar = pd.read_csv('data_old_bar.csv', encoding='cp949')
    make_bar(data_bar)


def read_file_2020():
    with open('2020년도_성별 학생수.json', 'r', encoding="UTF-8") as file:
        dic_data = json.load(file)
    df = pd.DataFrame.from_dict(dic_data['body'])

    sss = df.drop(df[(df[7] == 'Y')].index, inplace=True)  # 3405라인 예외처리
    # print('데이터 프레임',df)
    print('===============================================')
    print('2020~2022년도 초등학교 학생수 현황 V1.0')
    print('===============================================')
    st_class_sum_m = []
    st_class_sum_f = []
    st_sum_m = df[[9, 11, 13, 15, 17, 19]].sum()
    st_class_sum_m.append(st_sum_m)
    st_sum_f = df[[10, 12, 14, 16, 18, 20]].sum()
    st_class_sum_f.append(st_sum_f)
    # 남자여자 리스트를 담음
    # print(st_class_sum_m)
    # print(st_class_sum_f)
    total_sum_2020 = [0, 0, 0, 0, 0, 0]
    a1_m = st_sum_m
    a2_f = st_sum_f
    for i, (a1i, a2i) in enumerate(zip(a1_m, a2_f)):
        total_sum_2020[i] = a1i + a2i
    print('2020년도 학년별 학생수:', total_sum_2020)
    return total_sum_2020


def read_file_2020_mf():
    with open('2020년도_성별 학생수.json', 'r', encoding="UTF-8") as file:
        dic_data = json.load(file)
    df = pd.DataFrame.from_dict(dic_data['body'])

    sss = df.drop(df[(df[7] == 'Y')].index, inplace=True)  # 3405라인 예외처리
    # print('데이터 프레임',df)

    st_class_sum_m = []
    st_class_sum_f = []
    st_sum_m = df[[9, 11, 13, 15, 17, 19]].sum()
    st_class_sum_m.append(st_sum_m)
    print(st_class_sum_m)

    st_sum_f = df[[10, 12, 14, 16, 18, 20]].sum()
    st_class_sum_f.append(st_sum_f)
    print(st_class_sum_f)

    # 남자여자 리스트를 담음
    # print(st_class_sum_m)
    # print(st_class_sum_f)
    total_sum_2020 = [0, 0, 0, 0, 0, 0]
    a1_m = st_sum_m
    a2_f = st_sum_f
    for i, (a1i, a2i) in enumerate(zip(a1_m, a2_f)):
        total_sum_2020[i] = a1i + a2i
    print('2020년도 학년별 학생수:', total_sum_2020)
    return total_sum_2020


# 2021파일읽기
def read_file_2021():
    with open('2021년도_성별 학생수.json', 'r', encoding="UTF-8") as file:
        dic_data = json.load(file)
    df = pd.DataFrame.from_dict(dic_data['body'])

    sss = df.drop(df[(df[7] == 'Y')].index, inplace=True)  # 3405라인 예외처리
    st_class_sum_m = []
    st_class_sum_f = []
    st_sum_m = df[[9, 11, 13, 15, 17, 19]].sum()
    st_class_sum_m.append(st_sum_m)
    st_sum_f = df[[10, 12, 14, 16, 18, 20]].sum()
    st_class_sum_f.append(st_sum_f)
    total_sum_2021 = [0, 0, 0, 0, 0, 0]
    a1_m = st_sum_m
    a2_f = st_sum_f
    for i, (a1i, a2i) in enumerate(zip(a1_m, a2_f)):
        total_sum_2021[i] = a1i + a2i
    print('2021년도 학년별 학생수:', total_sum_2021)
    return total_sum_2021


# 2022파일읽기
def read_file_2022():
    with open('2022년도_성별 학생수.json', 'r', encoding="UTF-8") as file:
        dic_data = json.load(file)

    df = pd.DataFrame.from_dict(dic_data['body'])
    sss = df.drop(df[(df[7] == 'Y')].index, inplace=True)  # 3405라인 예외처리
    st_class_sum_m = []
    st_class_sum_f = []
    st_sum_m = df[[9, 11, 13, 15, 17, 19]].sum()
    st_class_sum_m.append(st_sum_m)
    st_sum_f = df[[10, 12, 14, 16, 18, 20]].sum()
    st_class_sum_f.append(st_sum_f)
    total_sum_2022 = [0, 0, 0, 0, 0, 0]
    a1_m = st_sum_m
    a2_f = st_sum_f
    for i, (a1i, a2i) in enumerate(zip(a1_m, a2_f)):
        total_sum_2022[i] = a1i + a2i
    print('2022년도 학년별 학생수:', total_sum_2022)
    print(type(total_sum_2022))  # 리스트
    return total_sum_2022


# 2020~2022년도 학생 리스트를 딕셔너리로 변경(인덱스 사용)딕셔너리로 변환하기
def change_array(total_sum_2020, total_sum_2021, total_sum_2022):
    class_list = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    yearlist = [2020, 2021, 2022]
    pro_20 = total_sum_2020  # 2020년 값
    pro_21 = total_sum_2021  # 2021년 값
    pro_22 = total_sum_2022  # 2022년 값
    tup = zip(class_list, zip(pro_20, pro_21, pro_22))
    dict_product = dict(tup)

    idx = yearlist
    # print(dict_product)
    df = pd.DataFrame(dict_product, index=idx)
    print('idx&columns-----------------------------------------------------------')
    print(df)
    print(type(df))
    print('===========시각화 시작===========')
    return df


# 시각화
def view_gp1(df):
    df.plot.bar(figsize=(13, 8), width=0.95, color=['#ff9999', '#ffc000', '#8fd9b6', 'silver', '#d395d0', '#b4bde9'])
    plt.title('2020~2022 초등학교 학생수 현황', fontsize=20)
    plt.xticks(rotation=0)
    plt.yticks(rotation=0)
    plt.xlabel('년도', fontsize=15)
    plt.ylabel('학생수', fontsize=15, rotation='horizontal')
    plt.legend(loc='best', ncol=6)
    plt.ylim(400000)
    plt.show()


# 원형 그래프 3개
def view_gp2(df, total_sum_2020, total_sum_2021, total_sum_2022):
    fig = plt.figure(figsize=(16, 6))
    fig.suptitle("2020~2022년 초등학교 학생수 현황", fontsize=20)

    plt.subplot(131)  # 2행2열 첫번째
    labels = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    color = ['#ff9999', '#ffc000', '#8fd9b6', 'silver', '#d395d0', '#b4bde9']

    values = total_sum_2020
    plt.title('2020년', fontsize=16)
    # plt.pie(values, labels=labels, autopct='%.1f%%',colors=color)
    plt.pie(values, labels=labels, autopct='%.1f%%', startangle=260, counterclock=False, colors=color)

    plt.subplot(132)  # 2행2열 첫번째
    values = total_sum_2021
    plt.title('2021년', fontsize=16)
    plt.pie(values, labels=labels, autopct='%.1f%%', startangle=260, counterclock=False, colors=color)

    plt.subplot(133)  # 2행2열 첫번째
    values = total_sum_2022
    plt.title('2022년', fontsize=16)
    plt.pie(values, labels=labels, autopct='%.1f%%', startangle=260, counterclock=False, colors=color)
    plt.legend(loc='lower right', ncol=6, bbox_to_anchor=(0.2, -0.1))  # 범례표시

    plt.tight_layout  # 위 아래 간격 자동 조절
    plt.show()


def view_gp3(df,total_sum_2020, total_sum_2021, total_sum_2022):
    ##학년별 최저 학생수를 구한다(함수내에서 바로 구함)
    hak_list = []
    hak_1 = df['1학년'].min()
    hak_list.append(hak_1)
    hak_2 = df['2학년'].min()
    hak_list.append(hak_2)
    hak_3 = df['3학년'].min()
    hak_list.append(hak_3)
    hak_4 = df['4학년'].min()
    hak_list.append(hak_4)
    hak_5 = df['5학년'].min()
    hak_list.append(hak_5)
    hak_6 = df['6학년'].min()
    hak_list.append(hak_6)
    print('최저값', hak_list)
    # 년도 상관없이 최저값 끝

    fig = plt.figure(figsize=(13, 8))
    fig.suptitle("2020~2022년 초등학교 학생수 현황", fontsize=20)
    list_x_1 = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    list_y_1 = total_sum_2020
    list_x_2 = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    list_y_2 = total_sum_2021
    list_x_3 = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    list_y_3 = total_sum_2022
    list_x_4 = ['1학년', '2학년', '3학년', '4학년', '5학년', '6학년']
    list_y_4 = hak_list

    plt.xlabel('학년', fontsize=15)
    plt.ylabel('학생수', fontsize=15, rotation='horizontal')
    plt.plot(list_x_1, list_y_1,
             color='skyblue',
             marker='o', markerfacecolor='blue',
             markersize=6, linestyle=":", linewidth='3')

    plt.plot(list_x_2, list_y_2,
             color='pink',
             marker='o', markerfacecolor='red',
             markersize=6, linestyle=":", linewidth='3')
    plt.plot(list_x_3, list_y_3,
             color='green',
             marker='o', markerfacecolor='darkgreen',
             markersize=6, linestyle=":", linewidth='3')

    plt.plot(list_x_4, list_y_4,
             color='#AC58FA',
             marker='o', markerfacecolor='#4C0B5F',
             markersize=6, linewidth='5')

    plt.legend(('2020년', '2021년', '2022년', '년도 구별없이 최저값'), loc='upper right', ncol=4)
    plt.show()


# 엑셀 저장
def write_excel(df):
    writer = pd.ExcelWriter('초등학생수_excel.xlsx',
                            engine='xlsxwriter')
    df.to_excel(writer, sheet_name='Sheet1')
    writer.close()

def student():
    koreanFont()
    total_sum_2020 = read_file_2020()
    total_sum_2021 = read_file_2021()
    total_sum_2022 = read_file_2022()
    df = change_array(total_sum_2020, total_sum_2021, total_sum_2022)

    # 엑셀,DB로 저장하기
    write_excel(df)

    # 시각화 하기
    view_gp1(df)  # 막대그래프
    view_gp2(df,total_sum_2020, total_sum_2021, total_sum_2022)  # 원형 그래프3개
    view_gp3(df, total_sum_2020, total_sum_2021, total_sum_2022)  # 최저값


def mask():
    title = []      #제목
    cost = []       #합가
    ori_day = []
    deal_type = []  #거래유형 ㅡ팝니다, 삽니다, 거래완료
    day=[] #오래된날짜가 index가 작도록,ori_day 역전
    good_num = []   #마스크 개수(cost/good_num=one_cost)
    ori_one_cost = []
    one_cost=[]     #오래된날짜의 단가가 index가 작도록,ori_one_cost 역전
    mon_cost = []   #월별로 평균값 구함
    month = []      #날짜를 월별로 합침

    for i in range(1, 19):
        if i==2 or i==13 or i==17: continue  #부적합한 정보 제외처리(2,13,17p 정보)

        driver = webdriver.Chrome()
        URL = f'https://www.ppomppu.co.kr/search_bbs.php?search_type=sub_memo&page_no={i}&keyword=kf94&page_size=20&bbs_id=&order_type=date&bbs_cate=3'
        driver.get(URL)
        html = driver.page_source
        driver.close()
        soup = BeautifulSoup(html, 'html.parser')

        for j in range(1, 21):

            #부적합한 정보 제외처리
            if ((i!=1 or j!=3)and (i!=1 or j!=4) and (i!=1 or j!=14)and (i!=1 or j!=15)and (i!=1 or j!=16) \
                              and (i!=3 or j!=1) and (i!=3 or j!=2) and (i!=3 or j!=20) \
                              and (i!=5 or j!=1) and (i!=5 or j!=2) and (i!=5 or j!=3) and (i!=5 or j!=4) and (i!=5 or j!=5)\
                              and (i!=5 or j!=6) and (i!=5 or j!=9) and (i!=5 or j!=13)and (i!=5 or j!=17) \
                              and (i!=6 or j!=18)and (i!=6 or j!=19)and (i!=6 or j!=20)  \
                              and (i!=7 or j!=1) and (i!=7 or j!=3) and (i!=7 or j!=6) and (i!=7 or j!=8) and (i!=7 or j!=9)\
                              and (i!=8 or j!=9) and (i!=8 or j!=13)and (i!=8 or j!=14)and (i!=8 or j!=15)and (i!=8 or j!=16) and (i!=8 or j!=18) and (i!=8 or j!=19)\
                ) and \
                ( i==1 or i==3 or i==5 or i==6 or i==7 or i==8 \
               or(i==4 and j==14)or (i==4 and j==15)or (i==4 and j==18) \
               or(i==9 and j==5) or (i==9 and j==7) or (i==9 and j==15) or (i==9 and j==20) \
               or(i==10 and j==2) \
               or(i==11 and j==4) or(i==11 and j==20) \
               or(i==12 and j==6) or(i==12 and j==7) or (i==12 and j==10) or (i==12 and j==12) or (i==12 and j==15) or (i==12 and j==18) \
               or(i==14 and j==14)or(i==14 and j==15) \
               or(i==15 and j==1) \
               or(i==16 and j==8) or(i==16 and j==14)or (i==16 and j==15) or (i==16 and j==17) \
               or(i==18 and j==12)or (i==18 and j==13) or (i==18 and j==14) or (i==18 and j==15) or (i==18 and j==18) \
               or(i==18 and j==19)or(i==18 and j==20)):
                #제목, 가격, 거래유형, 날짜가 모두 있는 항목만 크롤링위해
                if soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > span.title> a') \
                        and soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > strong') \
                        and soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > p.desc> span'):
                    if soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > p.desc> span')[
                        1].get_text() == '거래완료':  #삽니다, 팝니다, 거래완료 중에 거래완료 된 항목만 가져옴
                        title.append(soup.select(
                            f'form[name=search_result] > div > div:nth-child({j}) > div > span.title> a')[0].get_text()[:-1])
                        cost.append(soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > strong')[
                                        0].get_text())
                        ori_day.append(
                            soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > p.desc> span')[
                                2].get_text())
                        deal_type.append(
                            soup.select(f'form[name=search_result] > div > div:nth-child({j}) > div > p.desc> span')[
                                1].get_text())

    #제목(title)에서 숫자 중에 (kf)94와 마스크 개수만 있는 항목 외에는 제외처리함. 그러므로 94가 아닌 수가 good_num(마스크 개수)
    for i in range(len(title)):
        numbers = re.findall(r'\d+', title[i])
        if numbers[0] == '94':
            good_num.append(numbers[1])
        elif numbers[1] == '94':
            good_num.append(numbers[0])

    #합가(cost) 중에 ','제거 후, 개수(good_num)으로 나누어 단가 구함
    #소수점 제거
    for i in range(len(cost)):
        ori_one_cost.append(round(float(cost[i].replace(',', ''))/float(good_num[i])))

    #이전날짜가 index가 작도록,ori_day 역전
    #오래된날짜의 단가가 index가 작도록,ori_one_cost 역전
    for i in range(len(ori_day)):
        day.append(ori_day[len(ori_day)-1-i])
        one_cost.append(ori_one_cost[len(ori_one_cost) - 1 - i])

    #일별로 되어있는 데이터를 월별로 합치며, 월별로 단가의 평균값 구함
    c = 0
    for i in range(len(day)):
        if c != 0:
            c -= 1
            continue
        sum = one_cost[i]
        for j in range(len(day)):
            if i >= j: continue
            if day[i][:7] == day[j][:7]:
                c += 1
                sum += one_cost[j]
                if j == len(day) - 1:
                    month.append(day[i][:7])
                    mon_cost.append(round(sum / (c + 1)))  #소수점 제거
            else:
                month.append(day[i][:7])
                mon_cost.append(round(sum / (c + 1)))   #소수점 제거
                break

    total_list=[mon_cost, month]
    total_list2 = [title, ori_one_cost, ori_day, deal_type]

    print(total_list)
    print(len(total_list[0]))

    data = {
        '개당 가격': total_list[0],
        '날짜': total_list[1]
    }
    data2 = {
        '제목': total_list2[0],
        '개당 가격': total_list2[1],
        '날짜': total_list2[2],
        '거래유형': total_list2[3]
    }

    #딕셔너리를 데이터프레임으로 만들고 엑셀저장
    df = pd.DataFrame(data)
    print(df)
    writer = pd.ExcelWriter('mask3.xlsx',
                            engine='xlsxwriter')
    df.to_excel(writer, sheet_name='Sheet1')
    writer.close()

    df2 = pd.DataFrame(data2)
    print(df2)
    writer = pd.ExcelWriter('mask4.xlsx',
                            engine='xlsxwriter')
    df2.to_excel(writer, sheet_name='Sheet1')
    writer.close()

    #그래프의  x,y축 설정
    koreanFont()
    df.index = df.날짜
    data_y1 = df.loc[:, '개당 가격']
    x1 = data_y1.index
    y1 = data_y1
    fig, ax = plt.subplots()

    # ================= 데이터 시각화 =================#
    line1 = ax.plot(y1, 'o-', label='개당 가격(원)',
                    color='blue', linewidth=1)
    # 값 출력
    for i, v in enumerate(x1):
        plt.text(v, y1[i]+3, str(y1[i]) + '원', fontsize=12, color='black',
                 horizontalalignment='left',
                 verticalalignment='bottom',
                 rotation=15)
    plt.xticks(x1, fontsize=10, rotation=15)
    plt.yticks(fontsize=10)
    plt.xlabel('날짜', fontsize=17)
    plt.ylabel('개당 가격(원)', fontsize=17)
    plt.title('코로나 사태 속 마스크 가격 변동', fontsize=23)

    # 범례 표시
    lines = line1
    labels = [line.get_label() for line in lines]
    ax.legend(lines, labels, loc=1, fontsize=10)
    ax.grid()
    plt.show()
if __name__ == '__main__':
    selectn = 1
    select = 0
    while selectn:
        print('========================================')
        print('인구 파악 프로그램 v.1')
        print('========================================')
        print('메뉴를 선택해 주세요.')
        print('1. 코로나에 따른 마스크 가격변동 보기')
        print('2. 늘어나는 고령화. 지도 보기')
        print('3. 줄어드는 신생아. 다양한 분석 보기')
        print('4. 줄어드는 입학생. 살펴보기')
        print('5. 종료')
        print('========================================')
        select = input('메뉴 입력 : ')

        if select == '1':
            # 경녹님 파트. 코로나 상황에 따른 마스크 가격변동 시각화

            mask()
        elif select == '2':
            # 수인 파트. 노인 인구수 및 비율 시각화
            pltkorea.figure(figsize=(18, 10))
            oldman()
        elif select == '3':
            # 성혜님 파트. 신생아 인구 파악및 시각화.
            baby()
        elif select == '4':
            # 종욱님 파트. 학생수 감소 추이 파악및 시각화
            student()
        elif select == '5':
            selectn = False
            break
        else:
            print('잘못입력하셨습니다.')



