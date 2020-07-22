const family_names = "赵钱孙李周吴郑王冯陈褚"
const names = "思怡桑佳雪蘭婕翠翠絲珊蓉秋雲靈竹紫君昕欣月媚韻甜映秋紫寧笑藍梅彤嫦"

for (const i in family_names) {
    let fname = family_names[i];
    for (let k = 0; k < names.length; k += 2) {
        let name = fname + names.substr(k, 2);
        let cn = Math.round(Math.random() * 50 + 50);
        let en = Math.round(Math.random() * 50 + 50);
        let ma = Math.round(Math.random() * 50 + 50);

        console.log(`${name},${cn},${en},${ma},normal`);
    }
}
