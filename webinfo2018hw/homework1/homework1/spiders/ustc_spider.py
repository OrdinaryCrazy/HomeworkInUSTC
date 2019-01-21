import scrapy
from scrapy.selector import Selector
from homework1.items import Homework1Item

class USTCSpider(scrapy.Spider):
    name = "ustc"
    allowed_domains = ["ustc.edu.cn"]
    start_urls = [
        "https://www.ustc.edu.cn/"
    ]

    def parse(self, response):
        #url = response.urljoin(self.start_urls[0])
        #yield scrapy.Request(url,callback=self.parse_response)
        sel = Selector(response)
        sites = sel.xpath('//ul/div/li')
        #sites = sel.xpath('//ul/li')
        items = []
        for site in sites:
            item = Homework1Item()
            item['title'] = site.xpath('a/text()').extract()
            item['link'] = site.xpath('a/@href').extract()
            item['desc'] = site.xpath('text()').extract()
            items.append(item)
        #with open(filename, 'wb') as f:
            #f.write(response.body)
        return items
        
#########################################################################
    #def parse_response(self,response):
        #content_list = []
        #contents= response.xpath("//div[@class='j-r-list-c']/div[@class='j-r-list-c-desc']/a").xpath("string(.)").extract()
        
        #for content in contents:
            #new_item = Homework1Item()
            #new_item['content'] = content
            #content_list.append(new_item)
            #yield new_item
        #page_list=response.xpath("//div[@class='m-page m-page-sr m-page-sm']/a/@href").extract()
        
        #for page in page_list:
            #url = response.urljoin(page)
            #yield scrapy.Request(url,callback=parse_response)
    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
